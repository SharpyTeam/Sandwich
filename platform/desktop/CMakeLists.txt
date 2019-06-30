cmake_minimum_required(VERSION 3.13)
project(SandwichDesktop)

set(CMAKE_CXX_STANDARD 17)

include(deps/ucm/ucm.cmake)
ucm_set_runtime(STATIC)

add_subdirectory(../../core SandwichCore)

set(SANDWICH_DESKTOP_HEADERS
        )

set(SANDWICH_DESKTOP_SOURCES
        src/main.cpp)

add_executable(Sandwich ${SANDWICH_DESKTOP_HEADERS} ${SANDWICH_DESKTOP_SOURCES})
target_include_directories(Sandwich PRIVATE src)
target_link_libraries(Sandwich sandwich_core)