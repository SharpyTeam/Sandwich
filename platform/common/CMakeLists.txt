cmake_minimum_required(VERSION 3.13)
project(SandwichCommon)

set(CMAKE_CXX_STANDARD 17)

set(SANDWICH_COMMON_HEADERS
        src/gl.hpp)

set(SANDWICH_COMMON_SOURCES
        src/stub.cpp)

add_library(sandwich_common STATIC ${SANDWICH_COMMON_HEADERS} ${SANDWICH_COMMON_SOURCES})
target_include_directories(sandwich_common PRIVATE src include/sw/common)
target_include_directories(sandwich_common PUBLIC include)