execute_process(COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE error)

if(EXPECTED MATCHES "/invalid\\.expected$")
    set(expected_result "1")
    set(actual "${error}")
else()
    set(expected_result "0")
    set(actual "${output}")
endif()

file(READ "${EXPECTED}" expected)
string(REPLACE "\r\n" "\n" actual "${actual}")
string(REPLACE "\r\n" "\n" expected "${expected}")
if(NOT result STREQUAL expected_result OR NOT actual STREQUAL expected)
    message(FATAL_ERROR "Exit: ${result}, expected: ${expected_result}\nExpected:\n${expected}\nActual:\n${actual}\n${error}")
endif()
