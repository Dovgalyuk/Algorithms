if(NOT EXISTS "${PROGRAM}")
    message(FATAL_ERROR
        "Не найден исполняемый файл: ${PROGRAM}\n"
        "Сначала соберите проект (Build All), затем запустите тесты.")
endif()

if(NOT DEFINED EXPECTED_EXIT)
    set(EXPECTED_EXIT 0)
endif()

execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE exit_code
    OUTPUT_VARIABLE actual
    ERROR_VARIABLE actual_error
)

if(NOT "${exit_code}" STREQUAL "${EXPECTED_EXIT}")
    message(FATAL_ERROR
        "Ожидался код завершения ${EXPECTED_EXIT}, получен ${exit_code}.\n${actual_error}")
endif()

if(NOT actual_error STREQUAL "")
    message(FATAL_ERROR "Программа записала сообщение в stderr\n${actual_error}")
endif()

set(expected "")
if(DEFINED EXPECTED)
    file(READ "${EXPECTED}" expected)
    string(REPLACE "\r\n" "\n" expected "${expected}")
endif()

string(REPLACE "\r\n" "\n" actual "${actual}")
if(actual STREQUAL expected)
    return()
endif()

if(DEFINED EXPECTED_ALTERNATIVE)
    file(READ "${EXPECTED_ALTERNATIVE}" alternative)
    string(REPLACE "\r\n" "\n" alternative "${alternative}")
    if(actual STREQUAL alternative)
        return()
    endif()
    string(APPEND expected "\nВторой допустимый результат\n${alternative}")
endif()

message(FATAL_ERROR "Результат не совпадает.\nОжидалось:\n${expected}\nПолучено:\n${actual}")
