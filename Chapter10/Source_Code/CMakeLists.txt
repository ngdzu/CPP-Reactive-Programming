cmake_minimum_required(VERSION 3.0.0)
project(Tutorial VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(CustomOperator1 CustomOperator1.cpp)
add_executable(CustomOperator2 CustomOperator2.cpp)
add_executable(CustomOperatorScheduler CustomOperatorScheduler.cpp)
add_executable(OperatorLiftFirst OperatorLiftFirst.cpp)
add_executable(OperatorLiftSecond OperatorLiftSecond.cpp)


# create a library with custom configuration. 
# then we can link to this library to have that configuration in the targets
add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_17)
target_include_directories(tutorial_compiler_flags 
    INTERFACE "${PROJECT_SOURCE_DIR}/RxCpp-master/Rx/v2/src"
)

target_link_libraries(CustomOperator1 PUBLIC tutorial_compiler_flags)
target_link_libraries(CustomOperator2 PUBLIC tutorial_compiler_flags)
target_link_libraries(CustomOperatorScheduler PUBLIC tutorial_compiler_flags)
target_link_libraries(OperatorLiftFirst PUBLIC tutorial_compiler_flags)
target_link_libraries(OperatorLiftSecond PUBLIC tutorial_compiler_flags)




set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


