//---------- HotObservable.cpp
#include <rxcpp/rx.hpp>
#include <memory>

static const int s_emit_period = 500;
static const int s_num_take = 5;
static const int s_wait_time = 1200;


// NOTE [3] starts receives at 3 and lose the previous values because of hot observable
// [1] OnNext: 0
// [2] OnNext: 0
// [1] OnNext: 1
// [2] OnNext: 1
// [1] OnNext: 2
// [2] OnNext: 2
// [1] OnNext: 3
// [3] OnNext: 3 // [3] starts to receive at 3 because it waits 1.2sec before calling subscribe()
// [2] OnNext: 3
// [1] OnNext: 4
// [2] OnNext: 4
// [3] OnNext: 4
// [1] OnNext: 5
// [2] OnNext: 5
// [3] OnNext: 5
// [1] OnCompleted
// [2] OnCompleted
// [3] OnCompleted
void hotObservable()
{
       printf("HOT OBSERVABLE\n");
       auto values = rxcpp::observable<>::interval(std::chrono::milliseconds(s_emit_period), rxcpp::observe_on_new_thread()).take(s_num_take).publish(0L);

       // Subscribe from the beginning
       values.subscribe(
           [](long v) { printf("[1] OnNext: %ld\n", v); },
           []() { printf("[1] OnCompleted\n"); });
       // Another subscription from the beginning
       values.subscribe(
           [](long v) { printf("[2] OnNext: %ld\n", v); },
           []() { printf("[2] OnCompleted\n"); });

       // Start emitting
       // NOTE if we don't call connect, the observerble just emit once when we call subscribe(), then hang
       // [1] OnNext: 0
       // [2] OnNext: 0
       // [3] OnNext: 0
       values.connect();

       // Wait 1sec before calling subscribe()
       rxcpp::observable<>::timer(std::chrono::milliseconds(s_wait_time)).subscribe([&](long) {
              values.subscribe(
                  [](long v) { printf("[3] OnNext: %ld\n", v); },
                  []() { printf("[3] OnCompleted\n"); });
       });

       // wait for all the values to be emitted
       values.as_blocking().subscribe();
}

// NOTE the order is not synchronized
// COLD OBSERVABLE
// [1] OnNext: 1
// [2] OnNext: 1
// [1] OnNext: 2
// [2] OnNext: 2
// [2] OnNext: 3
// [1] OnNext: 3
// [2] OnNext: 4
// [1] OnNext: 4
// [3] OnNext: 1 <<<< [3] receives all the values from cold observable
// [3] OnNext: 2
// [3] OnNext: 3
// [3] OnNext: 4
// [3] OnNext: 5
// [1] OnNext: 5
// [2] OnNext: 5
// [3] OnCompleted
// [1] OnCompleted
// [2] OnCompleted
void coldObservable()
{
       printf("COLD OBSERVABLE\n");
       auto values = rxcpp::observable<>::interval(std::chrono::milliseconds(500), rxcpp::observe_on_new_thread()).take(5);

       // Subscribe from the beginning
       values.subscribe(
           [](long v) { printf("[1] OnNext: %ld\n", v); },
           []() { printf("[1] OnCompleted\n"); });
       // Another subscription from the beginning
       values.subscribe(
           [](long v) { printf("[2] OnNext: %ld\n", v); },
           []() { printf("[2] OnCompleted\n"); });

       // Wait 2sec before calling subscribe()
       // NOTE [3] will  only get the values emitted after 1.5 sec
       rxcpp::observable<>::timer(std::chrono::milliseconds(1500)).subscribe([&](long) {
              values.subscribe(
                  [](long v) { printf("[3] OnNext: %ld\n", v); },
                  []() { printf("[3] OnCompleted\n"); });
       });

       // NOTE block the main thread, allow the subscribers to receive all the values emitted
       values.as_blocking().subscribe();
}

int main(int argc, char *argv[])
{
       // hotObservable();

       coldObservable();
}
