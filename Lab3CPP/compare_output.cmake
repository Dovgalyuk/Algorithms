execute_process(
    COMMAND ${EXE} ${INPUT}
    OUTPUT_VARIABLE actual
    RESULT_VARIABLE result)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Program failed with code ${result}")
endif()
file(READ ${EXPECTED} expected)
string(REPLACE "\r\n" "\n" actual "${actual}")
string(REPLACE "\r\n" "\n" expected "${expected}")
string(STRIP "${actual}" actual)
string(STRIP "${expected}" expected)
if(NOT actual STREQUAL expected)
    message(FATAL_ERROR "Output differs.\nExpected:\n${expected}\nActual:\n${actual}")
endif()
