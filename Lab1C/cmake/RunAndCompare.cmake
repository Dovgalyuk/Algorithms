execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE actual
    ERROR_VARIABLE error_output
)

if(NOT result EQUAL 0)
    message(FATAL_ERROR "Program exited with code ${result}: ${error_output}")
endif()

file(READ "${EXPECTED}" expected)
if(NOT actual STREQUAL expected)
    message(FATAL_ERROR
        "Output does not match expected output.\n"
        "Expected:\n${expected}\n"
        "Actual:\n${actual}"
    )
endif()
