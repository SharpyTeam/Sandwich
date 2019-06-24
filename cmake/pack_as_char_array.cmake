if(NOT EXISTS ${INPUT_FILE})
    message(FATAL_ERROR "File '${INPUT_FILE}' does not exist!")
endif()

file(READ "${INPUT_FILE}" contents HEX)

file(WRITE "${OUTPUT_FILE}" "const char ${VARIABLE_NAME}[] = {")

string(LENGTH "${contents}" contents_length)

math(EXPR contents_length "${contents_length} - 1")

foreach(iter RANGE 0 ${contents_length} 2)
    string(SUBSTRING ${contents} ${iter} 2 line)
    file(APPEND "${OUTPUT_FILE}" "0x${line},")
endforeach()

file(APPEND "${OUTPUT_FILE}" "};\n")
