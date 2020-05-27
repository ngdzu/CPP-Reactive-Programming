cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)


# configure_file(TutorialConfig.h.in TutorialConfig.h)

add_executable(ColdObservable ColdObservable.cpp)
add_executable(HotObservable HotObservable.cpp)
add_executable(HotObservable2 HotObservable2.cpp)
add_executable(ReplayAll ReplayAll.cpp)
add_executable(Subscriber Subscriber.cpp)
add_executable(BehaviorSubject BehaviorSubject.cpp)
add_executable(ReplaySubject ReplaySubject.cpp)
add_executable(SchedulerOne SchedulerOne.cpp)
add_executable(SchedulerTwo SchedulerTwo.cpp)
add_executable(ObserveOnScheduler ObserveOnScheduler.cpp)
add_executable(SubscribeOnScheduler SubscribeOnScheduler.cpp)
add_executable(RunLoop RunLoop.cpp)


# create a library with custom configuration. 
# then we can link to this library to have that configuration in the targets
add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_17)
target_include_directories(tutorial_compiler_flags 
    INTERFACE "${PROJECT_SOURCE_DIR}/RxCpp-master/Rx/v2/src"
)

target_link_libraries(ColdObservable PUBLIC tutorial_compiler_flags)
target_link_libraries(HotObservable PUBLIC tutorial_compiler_flags)
target_link_libraries(HotObservable2 PUBLIC tutorial_compiler_flags)
target_link_libraries(ReplayAll PUBLIC tutorial_compiler_flags)
target_link_libraries(Subscriber PUBLIC tutorial_compiler_flags)
target_link_libraries(BehaviorSubject PUBLIC tutorial_compiler_flags)
target_link_libraries(ReplaySubject PUBLIC tutorial_compiler_flags)
target_link_libraries(SchedulerOne PUBLIC tutorial_compiler_flags)
target_link_libraries(ObserveOnScheduler PUBLIC tutorial_compiler_flags)
target_link_libraries(SubscribeOnScheduler PUBLIC tutorial_compiler_flags)
target_link_libraries(RunLoop PUBLIC tutorial_compiler_flags)
