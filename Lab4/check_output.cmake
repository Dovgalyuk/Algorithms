execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE actual
)

if(NOT result STREQUAL "0")
    message(FATAL_ERROR "Program exited with code ${result}")
endif()

file(READ "${EXPECTED}" expected)
string(REPLACE "\r\n" "\n" actual "${actual}")
string(REPLACE "\r\n" "\n" expected "${expected}")
string(STRIP "${actual}" actual)
string(STRIP "${expected}" expected)

if(NOT actual STREQUAL expected)
    message(FATAL_ERROR "Unexpected output.\nExpected:\n${expected}\nActual:\n${actual}")
endif()
