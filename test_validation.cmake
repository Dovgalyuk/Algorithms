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
if(NOT "${ACTUAL_OUTPUT}" MATCHES ".*Average value: 5.4.*" OR 
   NOT "${ACTUAL_OUTPUT}" MATCHES ".*Element closest to average: 5.1.*" OR
   NOT "${ACTUAL_OUTPUT}" MATCHES ".*Difference: 0.3.*" OR
   NOT "${ACTUAL_OUTPUT}" MATCHES ".*Compressed array: 12.5 4.7 15.2 0 0 0.*")
    message(FATAL_ERROR "Test failed: expected output not found.\nExpected key elements not found in:\n${ACTUAL_OUTPUT}")
else()
    message("Test passed successfully!")
endif()
