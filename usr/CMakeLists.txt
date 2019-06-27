cmake_minimum_required(VERSION 3.13)
project(Usr)

set(CMAKE_CXX_STANDARD 17)

add_custom_target(webpack_js
        COMMAND npx webpack
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_custom_command(
        OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/dist/js_bundle.c"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/dist/bundle.js"
        COMMAND "${CMAKE_COMMAND}"
        -D "INPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/dist/bundle.js"
        -D "OUTPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/dist/js_bundle.c"
        -D "VARIABLE_NAME=js_bundle_contents"
        -D "PACKER_FILE=${CMAKE_CURRENT_SOURCE_DIR}/../tools/pack_file.js"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/pack_as_char_array.cmake")

add_library(js_bundle STATIC "${CMAKE_CURRENT_SOURCE_DIR}/dist/js_bundle.c")
add_dependencies(js_bundle webpack_js)