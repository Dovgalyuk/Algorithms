execute_process(
    COMMAND "${PROGRAM}"
    INPUT_FILE "${INPUT}"
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error_output
    RESULT_VARIABLE result
)

if(NOT result EQUAL 0)
    message(FATAL_ERROR "Maze program failed (${result}): ${error_output}")
endif()

if("${INPUT}" MATCHES "test2\\.in$" AND NOT output MATCHES "No path")
    message(FATAL_ERROR "Expected 'No path' for ${INPUT}, got: ${output}")
endif()

