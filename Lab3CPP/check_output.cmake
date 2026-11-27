execute_process(COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE error)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Maze failed: ${result}: ${error}")
endif()
string(REPLACE "\r\n" "\n" output "${output}")
if(NOT output STREQUAL "${EXPECTED}\n")
    message(FATAL_ERROR "Expected '${EXPECTED}', got '${output}'")
endif()
