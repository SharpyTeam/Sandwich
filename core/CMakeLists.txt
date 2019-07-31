cmake_minimum_required(VERSION 3.13)
project(SandwichCore)

set(CMAKE_CXX_STANDARD 17)

# TODO Maybe allow relocating usr project?
add_subdirectory(../usr SandwichUsr)
#set(NO_GLSLCROSS_GLSL_TO_SPIRV_COMPILER TRUE)
add_subdirectory(../glslcross glslcross)

set(SANDWICH_CORE_HEADERS
        src/sw/object_wrap.hpp
        src/sw/sw_macros.hpp
        src/sw/core.hpp
        src/sw/math/vector.hpp
        src/sw/sprite.hpp src/sw/math/matrix.hpp src/sw/shader.hpp)

set(SANDWICH_CORE_SOURCES
        src/sw/core.cpp
        src/sw/sprite.cpp
        src/sw/math/vector.cpp src/sw/math/matrix.cpp)

add_library(sandwich_core STATIC ${SANDWICH_CORE_HEADERS} ${SANDWICH_CORE_SOURCES})

if (Debug STREQUAL ${CMAKE_BUILD_TYPE})
    set(V8_BUILD_TYPE debug)
else ()
    set(V8_BUILD_TYPE release)
endif ()

# TODO Rewrite on for js
#[[add_custom_target(V8Build COMMAND ${Python3_EXECUTABLE} v8_build.py ${V8_BUILD_TYPE} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tools")

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/v8_monolith_${V8_BUILD_TYPE}.lib" AND NOT
        EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/v8_monolith_${V8_BUILD_TYPE}.a")
    message(STATUS "V8 will be downloaded and built in ${V8_BUILD_TYPE} configuration")
    add_dependencies(Sandwich V8Build)
endif ()]]

target_include_directories(sandwich_core PUBLIC src deps/v8/include)
target_link_directories(sandwich_core PUBLIC lib)
target_link_libraries(sandwich_core "v8_monolith_${V8_BUILD_TYPE}" sandwich_usr_bundle glslcross)
if (WIN32)
    target_link_libraries(sandwich_core DbgHelp Winmm)
elseif (UNIX)
    target_link_libraries(sandwich_core pthread)
endif ()