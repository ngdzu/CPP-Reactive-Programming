//-------- ObservableOnScheduler.cpp

// after observe_on(), the rest will be exec in a different thread

#include "rxcpp/rx.hpp"
int main(){
    //------- Print the main thread id
    printf("Main Thread Id is %d\n", 
             std::this_thread::get_id());
    //-------- We are using observe_on here
    //-------- The Map will use the main thread
    //-------- Subscribed lambda will use a new thread
    rxcpp::observable<>::range(0,15).
        map([](int i){ 
            printf("Map %d : %d\n", std::this_thread::get_id(),i); // this will be exec in main thread
            return i;
        }).
        take(5).observe_on(rxcpp::synchronize_new_thread()). // after observe_on() with new thread, will be exec in different thread
        subscribe([&](int i){
           printf("Subs %d : %d\n", std::this_thread::get_id(),i); // this will be executed in a different thread
        });
    //----------- Wait for Two Seconds
    rxcpp::observable<>::timer(
       std::chrono::milliseconds(2000)).
       subscribe([&](long){ });
    
    return 0;
}