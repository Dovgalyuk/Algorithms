
execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE ACTUAL_EXIT_CODE
    OUTPUT_VARIABLE ACTUAL_OUTPUT
    ERROR_VARIABLE ACTUAL_ERROR
)

if(NOT ACTUAL_EXIT_CODE STREQUAL "${EXPECT_EXIT_CODE}")
    message(FATAL_ERROR
        "Expected exit code ${EXPECT_EXIT_CODE}, got ${ACTUAL_EXIT_CODE}\n"
        "Error: ${ACTUAL_ERROR}"
    )
endif()

if(DEFINED EXPECTED)
    string(STRIP "${ACTUAL_OUTPUT}" ACTUAL_OUTPUT)

    if(NOT ACTUAL_OUTPUT STREQUAL "${EXPECTED}")
        message(FATAL_ERROR
            "Expected output: '${EXPECTED}'\n"
            "Actual output: '${ACTUAL_OUTPUT}'"
        )
    endif()
endif()
