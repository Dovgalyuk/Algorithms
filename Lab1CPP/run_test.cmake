execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE exit_code
    OUTPUT_VARIABLE actual
    ERROR_VARIABLE actual_error
)

if(NOT exit_code EQUAL 0)
    message(FATAL_ERROR "Program failed with exit code ${exit_code}\n${actual_error}")
endif()

file(READ "${EXPECTED}" expected)

string(REPLACE "\r\n" "\n" actual "${actual}")
string(REPLACE "\r\n" "\n" expected "${expected}")

if(NOT actual STREQUAL expected)
    message(FATAL_ERROR "Output mismatch.\nExpected:\n${expected}\nActual:\n${actual}")
endif()
