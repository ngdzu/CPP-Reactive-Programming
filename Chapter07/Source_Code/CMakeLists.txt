cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)

# create a library with custom configuration. 
# then we can link to this library to have that configuration in the targets
add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_17)
target_include_directories(tutorial_compiler_flags 
    INTERFACE "${PROJECT_SOURCE_DIR}/RxCpp-master/Rx/v2/src"
)

# configure_file(TutorialConfig.h.in TutorialConfig.h)

add_executable(First First.cpp)
add_executable(Second Second.cpp)
add_executable(STLContainerStream STLContainerStream.cpp)
add_executable(Unsubscribe Unsubscribe.cpp)
add_executable(average average.cpp)
add_executable(scan scan.cpp)
add_executable(ObserveOn ObserveOn.cpp)
add_executable(ConcatMap ConcatMap.cpp)
add_executable(FlatMap FlatMap.cpp)
add_executable(Concat Concat.cpp)
add_executable(Merge Merge.cpp)
add_executable(TapExample TapExample.cpp)
add_executable(DeferExample DeferExample.cpp)
add_executable(BufferExample BufferExample.cpp)
add_executable(TimerExample TimerExample.cpp)


target_link_libraries(First PUBLIC tutorial_compiler_flags)
target_link_libraries(Second PUBLIC tutorial_compiler_flags)
target_link_libraries(STLContainerStream PUBLIC tutorial_compiler_flags)
target_link_libraries(Unsubscribe PUBLIC tutorial_compiler_flags)
target_link_libraries(average PUBLIC tutorial_compiler_flags)
target_link_libraries(scan PUBLIC tutorial_compiler_flags)
target_link_libraries(ObserveOn PUBLIC tutorial_compiler_flags)
target_link_libraries(ConcatMap PUBLIC tutorial_compiler_flags)
target_link_libraries(FlatMap PUBLIC tutorial_compiler_flags)
target_link_libraries(Concat PUBLIC tutorial_compiler_flags)
target_link_libraries(Merge PUBLIC tutorial_compiler_flags)
target_link_libraries(DeferExample PUBLIC tutorial_compiler_flags)
target_link_libraries(BufferExample PUBLIC tutorial_compiler_flags)
target_link_libraries(TimerExample PUBLIC tutorial_compiler_flags)
