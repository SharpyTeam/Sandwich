cmake_minimum_required(VERSION 3.13)
project(SandwichCore)

set(CMAKE_CXX_STANDARD 17)

# TODO Maybe allow relocating usr project?
add_subdirectory(../usr SandwichUsr)
add_subdirectory(../platform/common SandwichCommon)

set(SANDWICH_CORE_HEADERS
        src/object_wrap.hpp
        include/sw/core/core.hpp
        src/sw_macros.hpp
        src/math/vector.hpp)

set(SANDWICH_CORE_SOURCES
        src/core.cpp
        src/math/vector.cpp)

add_library(sandwich_core STATIC ${SANDWICH_CORE_HEADERS} ${SANDWICH_CORE_SOURCES})
target_include_directories(sandwich_core PUBLIC src)

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

target_include_directories(sandwich_core PRIVATE include/sw/core src deps/v8/include ../platform/common/include)
target_include_directories(sandwich_core PUBLIC include)
target_link_directories(sandwich_core PUBLIC lib)
target_link_libraries(sandwich_core "v8_monolith_${V8_BUILD_TYPE}" DbgHelp Winmm sandwich_usr_bundle sandwich_common)