cmake_minimum_required(VERSION 3.13)
project(SandwichRenderer)

set(CMAKE_CXX_STANDARD 17)

set(SANDWICH_RENDERER_HEADERS
        )

set(SANDWICH_RENDERER_SOURCES
        src/sw/renderer.cpp)

add_library(sandwich_renderer STATIC ${SANDWICH_RENDERER_HEADERS} ${SANDWICH_RENDERER_SOURCES})
target_include_directories(sandwich_renderer PUBLIC src)