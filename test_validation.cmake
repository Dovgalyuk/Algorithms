# Файл для проверки выходных данных тестов
execute_process(
    COMMAND ${TEST_COMMAND}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE ACTUAL_OUTPUT
    RESULT_VARIABLE EXIT_CODE
)

if(NOT EXIT_CODE EQUAL 0)
    message(FATAL_ERROR "Test failed with error: ${EXIT_CODE}")
endif()

# Проверяем наличие ожидаемого вывода
if(NOT "${ACTUAL_OUTPUT}" MATCHES ".*${EXPECTED_OUTPUT}.*")
    message(FATAL_ERROR "Test failed: expected output not found.\nExpected: ${EXPECTED_OUTPUT}\nActual: ${ACTUAL_OUTPUT}")
else()
    message("Test passed successfully!")
endif()
