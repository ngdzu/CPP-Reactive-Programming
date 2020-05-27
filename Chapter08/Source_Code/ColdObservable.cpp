//---------- ColdObservable.cpp
#include <rxcpp/rx.hpp>
#include <memory>

int main(int argc, char *argv[]) {

 //----------- Get a Coordination
 auto eventloop = rxcpp::observe_on_event_loop();
 //----- Create a Cold Observable
 auto values = rxcpp::observable<>::interval(
               std::chrono::seconds(2)).take(20);  
 //----- Subscribe Twice
 values.
    subscribe_on(eventloop).
    subscribe(
        [](int v){printf("[1] onNext: %d\n", v);},
        [](){printf("[1] onCompleted\n");});

 values.
    subscribe_on(eventloop).
    subscribe(
        [](int v){printf("[2] onNext: %d\n", v);},
        [](){printf("[2] onCompleted\n");});

 //---- make a blocking subscription to see the results
 // uncomment this to see from start to finish
//  values.as_blocking().subscribe();

 // The more time we wait, the more data will be printed out
 rxcpp::observable<>::timer(
       std::chrono::milliseconds(10000)).
       subscribe([&](long){ });

}

