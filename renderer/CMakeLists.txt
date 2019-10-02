cmake_minimum_required(VERSION 3.13)
project(SandwichRenderer)

set(CMAKE_CXX_STANDARD 17)

set(SANDWICH_RENDERER_HEADERS
        src/sw/shader.hpp
        src/sw/gl.hpp
        src/sw/texture_data.hpp
        src/sw/texture.hpp
        src/sw/texture_region.hpp src/sw/renderer.hpp src/sw/sprite_batch.hpp)

set(SANDWICH_RENDERER_SOURCES
        src/sw/renderer.cpp
        src/sw/shader.cpp src/sw/texture_data.cpp src/sw/texture.cpp src/sw/sprite_batch.cpp src/sw/texture_region.cpp)

set(ENABLE_HLSL FALSE)
add_subdirectory(deps/glslcross)

add_library(sandwich_renderer STATIC ${SANDWICH_RENDERER_HEADERS} ${SANDWICH_RENDERER_SOURCES})
target_include_directories(sandwich_renderer PUBLIC src)
target_link_libraries(sandwich_renderer sandwich_math glslcross)

if (TARGET_DESKTOP)
    find_package(OpenGL REQUIRED)

    add_subdirectory(deps/glew)
    add_subdirectory(deps/glfw)

    target_link_libraries(sandwich_renderer glew OpenGL::GL glfw)
endif ()