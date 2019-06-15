cmake_minimum_required(VERSION 3.10)
project(Sandwich)

set(CMAKE_CXX_STANDARD 17)

include(cmake/ucm.cmake)

ucm_set_runtime(STATIC)

add_executable(Sandwich src/main.cpp)
target_include_directories(Sandwich PUBLIC deps/v8/include)
target_link_directories(Sandwich PUBLIC lib)
target_link_libraries(Sandwich v8_monolith DbgHelp Winmm)