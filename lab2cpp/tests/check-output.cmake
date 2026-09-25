execute_process(
    COMMAND "${PROGRAM}" "${SCRIPT}" "${INPUT}"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error
)
if(NOT "${result}" STREQUAL "0")
    message(FATAL_ERROR "Program failed (exit ${result}): ${error}")
endif()
if(NOT "${output}" STREQUAL "${EXPECTED}")
    message(FATAL_ERROR "Expected <${EXPECTED}> but got <${output}>")
endif()