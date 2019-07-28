cmake_minimum_required(VERSION 3.14)
project(glslcross)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(thirdparty/glslang)
add_subdirectory(thirdparty/SPIRV-Cross)
add_library(glslcross STATIC src/main.cpp include/glslcross.h)
target_link_libraries(glslcross SPIRV spirv-cross-glsl)
target_include_directories(glslcross PUBLIC include)

if (NOT NO_GLSLCROSS_GLSL_TO_SPIRV_COMPILER)
    target_compile_definitions(glslcross PUBLIC GLSLCROSS_GLSL_TO_SPIRV_COMPILER=1)
endif ()