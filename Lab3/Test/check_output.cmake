execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE actual
    ERROR_VARIABLE error
)
if(NOT result STREQUAL "0")
    message(FATAL_ERROR "Lab3 exited with ${result}: ${error}")
endif()

file(READ "${EXPECTED}" expected)
string(REPLACE "\r\n" "\n" actual "${actual}")
string(REPLACE "\r\n" "\n" expected "${expected}")
if(NOT actual STREQUAL expected)
    message(FATAL_ERROR "Expected:\n${expected}\nActual:\n${actual}")
endif()
