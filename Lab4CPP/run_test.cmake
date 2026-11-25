execute_process(
    COMMAND ${PROG}
    INPUT_FILE ${INFILE}
    OUTPUT_VARIABLE actual
    RESULT_VARIABLE rc
)
if (NOT rc EQUAL 0)
    message(FATAL_ERROR "Program exited with ${rc}")
endif()

file(READ ${EXPFILE} expected)

string(STRIP "${actual}" actual_stripped)
string(STRIP "${expected}" expected_stripped)

if (NOT actual_stripped STREQUAL expected_stripped)
    message(FATAL_ERROR "Output mismatch.\nExpected:\n${expected_stripped}\nActual:\n${actual_stripped}")
endif()
