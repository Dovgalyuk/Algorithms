
execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE exit_code
    OUTPUT_VARIABLE actual
    ERROR_VARIABLE error_output
    TIMEOUT 10
)

string(STRIP "${actual}" actual)

if(NOT "${exit_code}" STREQUAL "0")
    message(FATAL_ERROR
        "Program failed: ${exit_code}\n${error_output}"
    )
endif()

if(NOT "${actual}" STREQUAL "${EXPECTED}")
    message(FATAL_ERROR
        "Wrong answer!\nExpected: ${EXPECTED}\nActual: ${actual}"
    )
endif()

message(STATUS "Passed: ${actual}")
