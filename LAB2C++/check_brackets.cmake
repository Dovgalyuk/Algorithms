
execute_process(
    COMMAND "${PROGRAM}" "${INPUT}" "${ACTUAL}"
    RESULT_VARIABLE PROGRAM_RESULT
)

if(NOT PROGRAM_RESULT EQUAL 0)
    message(FATAL_ERROR
        "The LAB2C++ program failed with code: ${PROGRAM_RESULT}"
    )
endif()

if(NOT EXISTS "${ACTUAL}")
    message(FATAL_ERROR "The output file was not created")
endif()

file(READ "${EXPECTED}" EXPECTED_CONTENT)
file(READ "${ACTUAL}" ACTUAL_CONTENT)

string(STRIP "${EXPECTED_CONTENT}" EXPECTED_CONTENT)
string(STRIP "${ACTUAL_CONTENT}" ACTUAL_CONTENT)

if(NOT "${ACTUAL_CONTENT}" STREQUAL "${EXPECTED_CONTENT}")
    message(FATAL_ERROR
        "Wrong answer.\n"
        "Expected: [${EXPECTED_CONTENT}]\n"
        "Actual:   [${ACTUAL_CONTENT}]"
    )
endif()

message(STATUS "LAB2C++ test passed: ${INPUT}")
