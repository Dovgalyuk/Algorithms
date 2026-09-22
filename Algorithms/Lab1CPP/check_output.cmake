execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE actual
    ERROR_VARIABLE error
    TIMEOUT 10
)
if (NOT "${result}" STREQUAL "0")
    message(FATAL_ERROR "Program failed (${result}): ${error}")
endif()

file(READ "${EXPECTED}" expected)
string(REPLACE "\r\n" "\n" actual "${actual}")
string(REPLACE "\r\n" "\n" expected "${expected}")
if (NOT "${actual}" STREQUAL "${expected}")
    message(FATAL_ERROR "Expected: [${expected}]\nActual: [${actual}]")
endif()
