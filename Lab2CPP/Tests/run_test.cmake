# Запускаем программу и сохраняем вывод
execute_process(
    COMMAND ${TASK_EXECUTABLE} ${SCRIPT_FILE} ${INPUT_FILE}
    OUTPUT_VARIABLE ACTUAL_OUTPUT
    RESULT_VARIABLE EXIT_CODE
    ERROR_VARIABLE ERROR_OUTPUT
)

# Проверяем, что программа не упала
if(NOT EXIT_CODE EQUAL 0)
    message(FATAL_ERROR "Test failed: program exited with code ${EXIT_CODE}\nError: ${ERROR_OUTPUT}")
endif()

# Читаем эталонный вывод
file(READ ${EXPECTED_FILE} EXPECTED_OUTPUT)

# Нормализуем вывод (убираем лишние пробелы в конце строк и \r)
string(REGEX REPLACE "[ \t]+\n" "\n" ACTUAL_OUTPUT "${ACTUAL_OUTPUT}")
string(REGEX REPLACE "[ \t]+\n" "\n" EXPECTED_OUTPUT "${EXPECTED_OUTPUT}")
string(REGEX REPLACE "\r" "" ACTUAL_OUTPUT "${ACTUAL_OUTPUT}")
string(REGEX REPLACE "\r" "" EXPECTED_OUTPUT "${EXPECTED_OUTPUT}")

# Сравниваем вывод
if(NOT "${ACTUAL_OUTPUT}" STREQUAL "${EXPECTED_OUTPUT}")
    message(FATAL_ERROR "Output mismatch!\n\nExpected:\n${EXPECTED_OUTPUT}\n\nActual:\n${ACTUAL_OUTPUT}")
endif()

message("Test passed!")