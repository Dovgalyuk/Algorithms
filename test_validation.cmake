# Файл для проверки выходных данных тестов
execute_process(
    COMMAND ${TEST_COMMAND}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE ACTUAL_OUTPUT
    RESULT_VARIABLE EXIT_CODE
)

if(NOT EXIT_CODE EQUAL 0)
    message(FATAL_ERROR "Тест завершился с ошибкой: ${EXIT_CODE}")
endif()

# Проверяем наличие ожидаемого вывода
if(NOT ACTUAL_OUTPUT MATCHES "${EXPECTED_OUTPUT}")
    message(FATAL_ERROR "Тест не прошел: ожидаемый вывод не найден.\nОжидалось: ${EXPECTED_OUTPUT}\nПолучено: ${ACTUAL_OUTPUT}")
else()
    message("Тест прошел успешно!")
endif()
