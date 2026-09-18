if(NOT DEFINED PROGRAM OR NOT DEFINED INPUT OR NOT DEFINED EXPECTED)
    message(FATAL_ERROR "Не заданы параметры теста")
endif()

execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    OUTPUT_VARIABLE ACTUAL
    ERROR_VARIABLE ERROR_TEXT
    RESULT_VARIABLE RESULT
)

if(NOT RESULT EQUAL 0)
    message(FATAL_ERROR "Программа завершилась с ошибкой:\n${ERROR_TEXT}")
endif()

file(READ "${EXPECTED}" EXPECTED_TEXT)

if(NOT ACTUAL STREQUAL EXPECTED_TEXT)
    message(FATAL_ERROR
        "Неверный результат.\n"
        "Ожидалось:\n${EXPECTED_TEXT}\n"
        "Получено:\n${ACTUAL}"
    )
endif()
