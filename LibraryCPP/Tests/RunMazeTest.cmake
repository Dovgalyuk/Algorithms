execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error_output
    RESULT_VARIABLE result
    TIMEOUT 10
)
if(NOT "${result}" STREQUAL "0")
    message(FATAL_ERROR "Maze program failed (${result}): ${error_output}")
endif()
file(READ "${EXPECTED}" expected_output)
string(REPLACE "\r\n" "\n" output "${output}")
string(REPLACE "\r\n" "\n" expected_output "${expected_output}")
if(NOT "${output}" STREQUAL "${expected_output}")
    message(FATAL_ERROR "Unexpected maze output.\nExpected:\n${expected_output}\nActual:\n${output}")
endif()
