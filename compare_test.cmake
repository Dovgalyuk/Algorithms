execute_process(
    COMMAND ${TEST_EXE} ${INPUT_FILE}
    OUTPUT_VARIABLE ACTUAL_OUTPUT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE EXIT_CODE
)

if(NOT EXIT_CODE EQUAL 0)
    message(FATAL_ERROR "Программа завершилась с ошибкой, код возврата ${EXIT_CODE}")
endif()

file(READ ${EXPECTED_FILE} EXPECTED_OUTPUT)
string(STRIP "${EXPECTED_OUTPUT}" EXPECTED_OUTPUT)

if(NOT ACTUAL_OUTPUT STREQUAL EXPECTED_OUTPUT)
    message(FATAL_ERROR "Результаты не совпадают.\nОжидалось: [${EXPECTED_OUTPUT}]\nПолучено:  [${ACTUAL_OUTPUT}]")
endif()
