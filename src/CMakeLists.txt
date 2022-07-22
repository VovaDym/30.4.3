cmake_minimum_required (VERSION 3.8)

project ("30.4.3")

set (CMAKE_CXX_STANDARD 20)

set(BUILD_CPR_TESTS OFF)
set(CMAKE_USE_OPENSSL OFF)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 6ea2dec23c3df14ac3b27b7d2d6bbff0cb7ba1b0) # The commit hash for 1.8.1. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

add_executable (30.4.3 "main.cpp")

target_link_libraries(30.4.3 PRIVATE cpr::cpr)
