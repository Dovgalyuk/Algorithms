execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE code
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error
    ERROR_STRIP_TRAILING_WHITESPACE
    ENCODING UTF-8
)

file(READ "${EXPECTED}" expected)
string(REPLACE "\r\n" "\n" output "${output}")
string(REPLACE "\r\n" "\n" expected "${expected}")

if(NOT "${code}" STREQUAL "${EXPECTED_CODE}")
    message(FATAL_ERROR "Unexpected exit code: ${code}")
endif()

if(NOT "${output}" STREQUAL "${expected}")
    message(FATAL_ERROR "Unexpected output:\n${output}\nExpected:\n${expected}")
endif()

if(NOT "${error}" STREQUAL "${EXPECTED_ERROR}")
    message(FATAL_ERROR "Unexpected error: ${error}")
endif()
