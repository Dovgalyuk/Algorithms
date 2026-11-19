
if(NOT DEFINED PROGRAM OR NOT DEFINED SCRIPT OR NOT DEFINED INPUT OR NOT DEFINED EXPECTED)
    message(FATAL_ERROR "Missing test arguments")
endif()

execute_process(
    COMMAND "${PROGRAM}" "${SCRIPT}" "${INPUT}"
    RESULT_VARIABLE exit_code
    OUTPUT_VARIABLE actual
    ERROR_VARIABLE error_output
)

file(READ "${EXPECTED}" expected)

if(NOT "${exit_code}" STREQUAL "0")
    message(FATAL_ERROR
        "Program exited with code: ${exit_code}\n${error_output}")
endif()

if(NOT "${actual}" STREQUAL "${expected}")
    message(FATAL_ERROR
        "Output mismatch!\n"
        "Expected: [${expected}]\n"
        "Actual:   [${actual}]\n"
        "Check spaces and newline characters.")
endif()

message(STATUS "Output matches expected")
