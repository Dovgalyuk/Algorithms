if(NOT EXISTS "${PROGRAM}")
    message(FATAL_ERROR
        "Не найден исполняемый файл: ${PROGRAM}\n"
        "Сначала соберите проект (Build All), затем запустите тесты.")
endif()

execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE exit_code
    OUTPUT_VARIABLE actual
    ERROR_VARIABLE actual_error
)

if(NOT exit_code EQUAL 0)
    message(FATAL_ERROR
        "Программа завершилась с ошибкой: ${exit_code}\n${actual_error}")
endif()

file(READ "${EXPECTED}" expected)

string(REPLACE "\r\n" "\n" actual "${actual}")
string(REPLACE "\r\n" "\n" expected "${expected}")

if(NOT actual STREQUAL expected)
    message(FATAL_ERROR
        "Результат не совпадает.\nОжидалось:\n${expected}\nПолучено:\n${actual}")
endif()
