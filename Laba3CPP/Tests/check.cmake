if(MODE STREQUAL "stdin")
    execute_process(COMMAND "${PROGRAM}"
        INPUT_FILE "${INPUT_FILE}"
        OUTPUT_VARIABLE actual
        ERROR_VARIABLE error
        RESULT_VARIABLE result)
else()
    execute_process(COMMAND "${PROGRAM}" "${INPUT_FILE}"
        OUTPUT_VARIABLE actual
        ERROR_VARIABLE error
        RESULT_VARIABLE result)
endif()

if(NOT result STREQUAL "0")
    message(FATAL_ERROR "Program failed (${result}): ${error}")
endif()

file(READ "${EXPECTED_FILE}" expected)
string(REPLACE "\r\n" "\n" actual "${actual}")
string(REPLACE "\r\n" "\n" expected "${expected}")
if(NOT actual STREQUAL expected)
    message(FATAL_ERROR "Expected:\n${expected}\nActual:\n${actual}")
endif()
