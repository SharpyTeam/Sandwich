cmake_minimum_required(VERSION 3.13)
project(Usr)

set(CMAKE_CXX_STANDARD 17)

add_custom_target(sandwich_build_js
        COMMAND npx webpack
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/dist/bundle.js")
set(OUTPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/dist/js_bundle.c")

add_custom_command(
        OUTPUT ${OUTPUT_FILE}
        DEPENDS ${INPUT_FILE}
        COMMAND node "${CMAKE_CURRENT_SOURCE_DIR}/../tools/pack_file.js"
        ${INPUT_FILE} ${OUTPUT_FILE} "js_bundle_contents")

add_library(sandwich_usr_bundle STATIC "${CMAKE_CURRENT_SOURCE_DIR}/dist/js_bundle.c")
add_dependencies(sandwich_usr_bundle sandwich_build_js)

# node test case
add_subdirectory(../tools/node Node)
add_custom_target(lel COMMAND ${NODE_COMMAND} -p \"'running s' + 0 + 'me shitty js'\")
add_dependencies(sandwich_build_js lel)