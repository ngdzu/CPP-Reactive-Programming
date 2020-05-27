//------------- ReplaySubject.cpp
#include <rxcpp/rx.hpp>
#include <memory>
int main(int argc, char *argv[])
{

    //----------- instantiate a ReplaySubject
    rxcpp::subjects::replay<int, rxcpp::observe_on_one_worker>
        replay_subject(5, rxcpp::observe_on_new_thread()); // cache the last 5 items

    //---------- get the observable interface
    auto observable = replay_subject.get_observable();
    //---------- Subscribe!
    observable.subscribe([](int v) {
        printf("1------%d\n", v);
    });
    //--------- get the subscriber interface
    auto subscriber = replay_subject.get_subscriber();
    //---------- Emit data
    int i = 1;
    subscriber.on_next(i++);
    subscriber.on_next(i++);
    subscriber.on_next(i++);
    subscriber.on_next(i++);
    subscriber.on_next(i++);
    subscriber.on_next(i++);
    subscriber.on_next(i++);
    subscriber.on_next(i++);
    subscriber.on_next(i++);
    subscriber.on_next(i++);

    //-------- Add a new subscriber
    //-------- A normal subject will drop data
    //-------- Replay subject will not
    // [2] will get the last 5 items from replay subject
    observable.subscribe([](int v) {
        printf("2------%d\n", v);
    });

    //----------- Wait for Two Seconds
    rxcpp::observable<>::timer(
        std::chrono::milliseconds(10000))
        .subscribe([&](int v) {});
}
