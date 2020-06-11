cmake_minimum_required(VERSION 3.0.0)
project(Tutorial VERSION 0.1.0)

include(CTest)
enable_testing()


if(CMAKE_HOST_WIN32)
  # then section.
  set(RXCPP_INC "D:/Data/Documents/Development/RxCpp/Rx/v2/src")
  set(CURL_DIR "C:/Program Files (x86)/CURL")
  find_package(CURL CONFIG REQUIRED) 
elseif(APPLE)
    set(RXCPP_INC "/usr/local/include")
    set(CURL_PATH "/usr/local/Cellar/curl/7.70.0")
    find_library(
        LIB_CURL
        NAMES
            curl
        PATHS 
            ${CURL_PATH}/lib)
endif()


add_executable(RxCurlDbClient RxCurlDbClient.cpp)
add_executable(RxCurlExample RxCurlExample.cpp)
add_executable(SimpleCurl SimpleCurl.cpp)


# create a library with custom configuration. 
# then we can link to this library to have that configuration in the targets
add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_14)
target_include_directories(tutorial_compiler_flags 
    INTERFACE "${RXCPP_INC}"
)

if(CMAKE_HOST_WIN32)
    target_link_libraries(tutorial_compiler_flags INTERFACE CURL::libcurl)
elseif(APPLE)
    target_link_libraries(tutorial_compiler_flags INTERFACE ${LIB_CURL})
endif()

target_link_libraries(RxCurlDbClient PUBLIC tutorial_compiler_flags)
target_link_libraries(RxCurlExample PUBLIC tutorial_compiler_flags)
target_link_libraries(SimpleCurl PUBLIC tutorial_compiler_flags)



# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)


