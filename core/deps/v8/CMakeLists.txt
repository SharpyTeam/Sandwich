cmake_minimum_required(VERSION 3.10)

project(V8)

add_library(v8::v8 STATIC IMPORTED GLOBAL)

set_target_properties(v8::v8 PROPERTIES IMPORTED_LOCATION_RELEASE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}v8_monolith_release${CMAKE_STATIC_LIBRARY_SUFFIX}")
set_target_properties(v8::v8 PROPERTIES IMPORTED_LOCATION_DEBUG
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}v8_monolith_debug${CMAKE_STATIC_LIBRARY_SUFFIX}")

# TODO add actual building steps
target_include_directories(v8::v8 INTERFACE include)