
set(input_file "${TEST_DIR}/input${TEST_NUMBER}.txt")
set(expected_file "${TEST_DIR}/expected${TEST_NUMBER}.txt")
set(output_file "${TEST_DIR}/output.txt")

file(COPY_FILE "${input_file}" "${TEST_DIR}/input.txt")
file(REMOVE "${output_file}")

execute_process(
    COMMAND "${PROGRAM}"
    WORKING_DIRECTORY "${TEST_DIR}"
    RESULT_VARIABLE result
)

if (NOT result EQUAL 0)
    message(FATAL_ERROR "Lab3CPP execution failed for test ${TEST_NUMBER}")
endif()

file(READ "${expected_file}" expected)
file(READ "${output_file}" actual)

string(STRIP "${expected}" expected)
string(STRIP "${actual}" actual)

if (NOT actual STREQUAL expected)
    message(FATAL_ERROR
        "Test ${TEST_NUMBER} failed.\nExpected: ${expected}\nActual: ${actual}"
    )
endif()

message(STATUS "Test ${TEST_NUMBER} passed")

