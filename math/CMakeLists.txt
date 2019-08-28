cmake_minimum_required(VERSION 3.13)
project(SandwichMath)

set(CMAKE_CXX_STANDARD 17)

set(SANDWICH_MATH_HEADERS
        src/matrix.hpp
        src/vector.hpp)

set(SANDWICH_MATH_SOURCES
        src/matrix.cpp
        src/vector.cpp)

add_library(sandwich_math STATIC ${SANDWICH_MATH_HEADERS} ${SANDWICH_MATH_SOURCES})
target_include_directories(sandwich_math PUBLIC src)