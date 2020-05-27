//---------- HotObservable2.cpp
#include <rxcpp/rx.hpp>
#include <memory>
#include <thread>
#include <chrono>

static const int s_emit_period = 500;
static const int s_num_take = 30;
static const int s_wait_time = 1200;

void little_sleep(std::chrono::milliseconds sec)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + sec;
    do {
        std::this_thread::yield();
    } while (std::chrono::high_resolution_clock::now() < end);
}

// QUESTION: publish_synchronized() What is really the difference between publish_synchronized() and publish() ????????????????
// with publish_synchronized() [3] doesn't chime in until 17
// with publish() [3] chime in at 3
// [1] OnNext: 1
// [2] OnNext: 1
// [1] OnNext: 2
// [2] OnNext: 2
// [1] OnNext: 3
// [2] OnNext: 3
// [1] OnNext: 4
// [2] OnNext: 4
// [1] OnNext: 5
// [2] OnNext: 5
// [1] OnCompleted
// [2] OnCompleted
// [3] OnCompleted // with publish_synchronized
int main(int argc, char *argv[])
{
       auto values = rxcpp::observable<>::interval(std::chrono::milliseconds(s_emit_period)).take(s_num_take).publish_synchronized(rxcpp::observe_on_new_thread());
       // auto values = rxcpp::observable<>::interval(std::chrono::milliseconds(s_emit_period)).take(s_num_take).publish(rxcpp::observe_on_new_thread());
       // auto values = rxcpp::observable<>::interval(std::chrono::milliseconds(s_emit_period), rxcpp::observe_on_new_thread()).take(s_num_take).publish(0L);

       // Subscribe from the beginning
       values.subscribe(
           [](long v) {
                  using namespace std::chrono_literals;
                  little_sleep(1000ms); // even if we yield other thread, [2] will not receive until [1] receive
                  printf("[1] OnNext: %ld\n", v);
           },
           []() { printf("[1] OnCompleted\n"); });

       // Another subscription from the beginning
       values.subscribe(
           [](long v) { printf("[2] OnNext: %ld\n", v); },
           []() { printf("[2] OnCompleted\n"); });

       // Start emitting
       // NOTE connect() may take a while to finish. That allows all the subscribers before this point
       // to receive a few item
       values.connect();

       // // Wait before subscribing
       rxcpp::observable<>::timer(std::chrono::milliseconds(s_wait_time)).subscribe([&](long) {
              values.subscribe(
                  [](long v) { printf("[3] OnNext: %ld\n", v); },
                  []() { printf("[3] OnCompleted\n"); });
       });

       // we need to block the main thread so that all the subscribers can receive all the items
       values.as_blocking().subscribe();
}
