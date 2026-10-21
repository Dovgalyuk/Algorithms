execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE result_code
    OUTPUT_VARIABLE actual_output
    ERROR_VARIABLE error_output
)

if(NOT result_code EQUAL 0)
    message(FATAL_ERROR
        "Program finished with error code ${result_code}\n"
        "${error_output}"
    )
endif()

file(READ "${EXPECTED}" expected_output)

string(REPLACE "\r" "" actual_output "${actual_output}")
string(REPLACE "\r" "" expected_output "${expected_output}")

string(STRIP "${actual_output}" actual_output)
string(STRIP "${expected_output}" expected_output)

if(NOT actual_output STREQUAL expected_output)
    message(FATAL_ERROR
        "Output is incorrect.\n"
        "Expected:\n${expected_output}\n\n"
        "Actual:\n${actual_output}\n"
    )
endif()