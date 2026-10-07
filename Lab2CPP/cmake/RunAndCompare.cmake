execute_process(
    COMMAND "${PROGRAM}" "${SCRIPT}" "${INPUT}"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE actual
    ERROR_VARIABLE error_output
    TIMEOUT 5
)

if(EXPECTED_ERROR)
    if(NOT "${result}" STREQUAL "1")
        message(FATAL_ERROR "Expected exit code 1, got ${result}: ${error_output}")
    endif()
    string(FIND "${error_output}" "${EXPECTED_ERROR}" error_position)
    if(error_position EQUAL -1)
        message(FATAL_ERROR "Expected diagnostic '${EXPECTED_ERROR}', got: ${error_output}")
    endif()
else()
    if(NOT "${result}" STREQUAL "0")
        message(FATAL_ERROR "Program exited with code ${result}: ${error_output}")
    endif()
    if(NOT "${error_output}" STREQUAL "")
        message(FATAL_ERROR "Unexpected stderr: ${error_output}")
    endif()
endif()

file(READ "${EXPECTED}" expected)
if(NOT "${actual}" STREQUAL "${expected}")
    message(FATAL_ERROR "Output mismatch.\nExpected:\n${expected}\nActual:\n${actual}")
endif()
