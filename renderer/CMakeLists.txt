cmake_minimum_required(VERSION 3.13)
project(SandwichRenderer)

set(CMAKE_CXX_STANDARD 17)

set(SANDWICH_RENDERER_HEADERS
        src/sw/shader.hpp src/sw/gl.hpp)

set(SANDWICH_RENDERER_SOURCES
        src/sw/renderer.cpp src/sw/shader.cpp)

set(ENABLE_HLSL FALSE)
add_subdirectory(deps/glslcross)

add_library(sandwich_renderer STATIC ${SANDWICH_RENDERER_HEADERS} ${SANDWICH_RENDERER_SOURCES})
target_include_directories(sandwich_renderer PUBLIC src)
target_link_libraries(sandwich_renderer sandwich_math glslcross)

if (TARGET_DESKTOP)
    find_package(OpenGL REQUIRED)

    add_subdirectory(deps/glfw)
    add_subdirectory(deps/glew)

    target_link_libraries(sandwich_renderer ${OPENGL_gl_LIBRARY} glew glfw)
endif ()