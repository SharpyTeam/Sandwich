if(NOT EXISTS ${INPUT_FILE})
    message(FATAL_ERROR "File '${INPUT_FILE}' does not exist!")
endif()

execute_process(COMMAND node "${PACKER_FILE}" "${INPUT_FILE}" "${OUTPUT_FILE}" "${VARIABLE_NAME}")
