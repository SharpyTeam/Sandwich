cmake_minimum_required(VERSION 3.13)
project(SandwichCore)

set(CMAKE_CXX_STANDARD 17)

set(SANDWICH_CORE_HEADERS
        src/sw/core/sw_macros.hpp
        src/sw/core.hpp
        src/sw/scene_node.hpp
        src/sw/scene.hpp
        src/sw/sprite.hpp
        src/sw/core/intrusive_pointer_manager.hpp
        src/sw/renderer/shader.hpp
        src/sw/renderer/gl.hpp
        src/sw/renderer/texture_data.hpp
        src/sw/renderer/texture.hpp
        src/sw/renderer/texture_region.hpp
        src/sw/renderer/renderer.hpp
        src/sw/renderer/sprite_batch.hpp)

set(SANDWICH_CORE_SOURCES
        src/sw/core.cpp
        src/sw/scene_node.cpp
        src/sw/scene.cpp
        src/sw/sprite.cpp
        src/sw/renderer/renderer.cpp
        src/sw/renderer/shader.cpp
        src/sw/renderer/texture_data.cpp
        src/sw/renderer/texture.cpp
        src/sw/renderer/sprite_batch.cpp
        src/sw/renderer/texture_region.cpp)

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
target_include_directories(sandwich_core PUBLIC src)

set(TOOLS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../tools")
add_subdirectory(../tools/node Node)

add_subdirectory(deps/math)
add_subdirectory(deps/v8)
get_target_property(V8_INCLUDE_DIR v8::v8 INTERFACE_INCLUDE_DIRECTORIES)
add_subdirectory(deps/v8bind)
add_subdirectory(deps/intrusive_ptr)
add_subdirectory(deps/glslcross)

if (TARGET_DESKTOP)
    add_subdirectory(deps/glew)
    add_subdirectory(deps/glfw)
    target_link_libraries(sandwich_core libglew_static glfw)
endif ()

target_link_libraries(sandwich_core
        v8::v8
        intrusive_ptr
        sw::math
        v8bind
        glslcross)

if (WIN32)
    target_link_libraries(sandwich_core DbgHelp Winmm)
elseif (UNIX)
    target_link_libraries(sandwich_core pthread dl)
endif ()

# ==================== build user project ====================
set(SANDWICH_USER_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../usr")

add_custom_target(sandwich_user_init
        COMMAND ${NPM_COMMAND} i
        WORKING_DIRECTORY "${SANDWICH_USER_PROJECT_DIR}")

add_custom_target(sandwich_user_bundle
        COMMAND ${NPX_COMMAND} webpack
        WORKING_DIRECTORY "${SANDWICH_USER_PROJECT_DIR}")

set(USER_INPUT_BUNDLE_FILE "${SANDWICH_USER_PROJECT_DIR}/dist/bundle.js")
set(USER_OUTPUT_BUNDLE_FILE "${CMAKE_CURRENT_BINARY_DIR}/user_bundle.c")

add_custom_command(
        OUTPUT ${USER_OUTPUT_BUNDLE_FILE}
        DEPENDS ${USER_INPUT_BUNDLE_FILE}
        COMMAND ${NODE_COMMAND} "${TOOLS_DIR}/pack_file.js"
        ${USER_INPUT_BUNDLE_FILE} ${USER_OUTPUT_BUNDLE_FILE} "js_bundle_contents")

add_library(sandwich_user STATIC "${CMAKE_CURRENT_BINARY_DIR}/user_bundle.c")
add_dependencies(sandwich_user_bundle sandwich_user_init)
add_dependencies(sandwich_user sandwich_user_bundle)

target_link_libraries(sandwich_core sandwich_user)