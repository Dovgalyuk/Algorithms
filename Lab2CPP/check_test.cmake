execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error
    TIMEOUT 5
)

if(NOT "${result}" STREQUAL "${EXPECTED_CODE}")
    message(FATAL_ERROR
        "Expected exit code ${EXPECTED_CODE}, got: ${result}\n${error}")
endif()

file(READ "${EXPECTED_BASE}.out" expected_output)
file(READ "${EXPECTED_BASE}.err" expected_error)

string(REPLACE "\r\n" "\n" output "${output}")
string(REPLACE "\r\n" "\n" error "${error}")

if(NOT "${output}" STREQUAL "${expected_output}")
    message(FATAL_ERROR
        "Wrong output.\nExpected:\n${expected_output}\nActual:\n${output}")
endif()

if(NOT "${error}" STREQUAL "${expected_error}")
    message(FATAL_ERROR
        "Wrong error message.\nExpected:\n${expected_error}\nActual:\n${error}")
endif()