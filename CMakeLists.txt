cmake_minimum_required(VERSION 3.13)
project(Sandwich)

set(CMAKE_CXX_STANDARD 17)
set(PYTHON_MIN_V_REQUIRED 7)

include(deps/ucm/ucm.cmake)

ucm_set_runtime(STATIC)

add_executable(Sandwich src/main.cpp)

if (Debug STREQUAL ${CMAKE_BUILD_TYPE})
    set(V8_BUILD_TYPE debug)
else ()
    set(V8_BUILD_TYPE release)
endif ()

find_package(Python3 COMPONENTS Interpreter)

if (${Python3_VERSION_MINOR} GREATER_EQUAL ${PYTHON_MIN_V_REQUIRED})
    message(STATUS "Found Python 3.${Python3_VERSION_MINOR}")
else ()
    message(FATAL_ERROR "Python 3.7 or newer is required to build the project. Aborting.")
endif ()

add_custom_target(V8Build COMMAND ${Python3_EXECUTABLE} v8_build.py ${V8_BUILD_TYPE} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tools")


if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/v8_monolith_${V8_BUILD_TYPE}.lib" AND NOT
        EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/v8_monolith_${V8_BUILD_TYPE}.a")
    message(STATUS "V8 will be downloaded and built in ${V8_BUILD_TYPE} configuration")
    add_dependencies(Sandwich V8Build)
endif ()

target_include_directories(Sandwich PUBLIC deps/v8/include)
target_link_directories(Sandwich PUBLIC lib)
target_link_libraries(Sandwich "v8_monolith_${V8_BUILD_TYPE}" DbgHelp Winmm)