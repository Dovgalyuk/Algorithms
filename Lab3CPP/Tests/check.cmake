execute_process(
    COMMAND "${PROGRAM}"
    INPUT_FILE "${INPUT}"
    OUTPUT_VARIABLE actual
    RESULT_VARIABLE result
)

file(READ "${EXPECTED}" expected)

if(NOT result EQUAL 0 OR NOT actual STREQUAL expected)
    message(FATAL_ERROR "KnightPath test failed.\nExpected:\n${expected}\nActual:\n${actual}")
endif()
