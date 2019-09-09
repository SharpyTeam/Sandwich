cmake_minimum_required(VERSION 3.13)
project(SandwichCore)

set(CMAKE_CXX_STANDARD 17)

set(SANDWICH_CORE_HEADERS
        src/sw/sw_macros.hpp
        src/sw/core.hpp
        src/sw/js_module.hpp
        #src/sw/modules/math.hpp
        #src/sw/scene_node.hpp
        #src/sw/scene.hpp
        #src/sw/intrusive_pointer_manager.hpp
)

set(SANDWICH_CORE_SOURCES
        src/sw/core.cpp
        #src/sw/modules/math.cpp
        #src/sw/scene_node.cpp
        #src/sw/scene.cpp
)


if (Debug STREQUAL ${CMAKE_BUILD_TYPE})
    set(V8_BUILD_TYPE debug)
else ()
    set(V8_BUILD_TYPE release)
endif ()

if (ANDROID OR IOS)
    if (ANDROID)
        set(TARGET_ANDROID TRUE)
        add_definitions(-DTARGET_ANDROID=1)
        if (ANDROID_ON_WINDOWS)
            message(STATUS "Compiling for Android on Windows")
        elseif (ANDROID_ON_MACOS)
            message(STATUS "Compiling for Android on macOS")
        elseif (ANDROID_ON_LINUX)
            message(STATUS "Compiling for Android on Linux")
        endif ()
    elseif (IOS)
        set(TARGET_IOS TRUE)
        add_definitions(-DTARGET_IOS=1)
        message(STATUS "Compiling for iOS on macOS")
    endif ()
    set(TARGET_MOBILE TRUE)
    set(RENDERER_GLES TRUE)
    set(SHADERS_TARGET_LANG gles)
    set(SHADERS_TARGET_PROFILE 100)
    add_definitions(-DTARGET_MOBILE=1 -DRENDERER_GLES=1)
elseif (WIN32 OR APPLE OR UNIX)
    if (WIN32)
        set(TARGET_WINDOWS TRUE)
        add_definitions(-DTARGET_WINDOWS=1)
        message(STATUS "Compiling for Windows")
    elseif (APPLE)
        set(TARGET_MACOS TRUE)
        add_definitions(-DTARGET_MACOS=1)
        message(STATUS "Compiling for macOS")
    elseif (UNIX)
        set(TARGET_LINUX TRUE)
        add_definitions(-DTARGET_LINUX=1)
        message(STATUS "Compiling for Linux")
    endif ()
    set(TARGET_DESKTOP TRUE)
    set(RENDERER_GL TRUE)
    set(SHADERS_TARGET_LANG glsl)
    set(SHADERS_TARGET_PROFILE 330)
    add_definitions(-DTARGET_DESKTOP=1 -DRENDERER_GL=1)
endif ()

# core target
add_library(sandwich_core STATIC ${SANDWICH_CORE_HEADERS} ${SANDWICH_CORE_SOURCES})
target_include_directories(sandwich_core PUBLIC deps/v8/include src)

# TODO Maybe allow relocating usr project?
add_subdirectory(../usr SandwichUsr)
#set(NO_GLSLCROSS_GLSL_TO_SPIRV_COMPILER TRUE)
add_subdirectory(../math SandwichMath)
add_subdirectory(../renderer SandwichRenderer)
set(V8_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/v8/include")
add_subdirectory(deps/v8bind)
add_subdirectory(deps/intrusive_ptr)
add_subdirectory(deps/v8pp)
target_include_directories(v8pp PUBLIC deps/v8/include)

# TODO Rewrite on for js
#[[add_custom_target(V8Build COMMAND ${Python3_EXECUTABLE} v8_build.py ${V8_BUILD_TYPE} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tools")

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/v8_monolith_${V8_BUILD_TYPE}.lib" AND NOT
        EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/v8_monolith_${V8_BUILD_TYPE}.a")
    message(STATUS "V8 will be downloaded and built in ${V8_BUILD_TYPE} configuration")
    add_dependencies(Sandwich V8Build)
endif ()]]

target_link_directories(sandwich_core PUBLIC lib)
target_link_libraries(sandwich_core
        "v8_monolith_${V8_BUILD_TYPE}"
        #intrusive_ptr
        sandwich_usr_bundle
        sandwich_math
        sandwich_renderer
        v8pp
        v8bind)
if (WIN32)
    target_link_libraries(sandwich_core DbgHelp Winmm)
elseif (UNIX)
    target_link_libraries(sandwich_core pthread dl)
endif ()