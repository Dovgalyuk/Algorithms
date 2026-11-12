# Аргументы, которые будут передаваться из CMakeLists.txt:
# -DPROGRAM_EXE (путь к программе)
# -DINPUT_FILE (путь к входному файлу)
# -DEXPECTED_FILE (путь к файлу с ожидаемым ответом)

execute_process(
    COMMAND ${PROGRAM_EXE}
    INPUT_FILE ${INPUT_FILE}
    OUTPUT_VARIABLE ACTUAL_OUTPUT
    RESULT_VARIABLE EXEC_RESULT
)

if(NOT EXEC_RESULT EQUAL 0)
    message(FATAL_ERROR "Program exited with error code ${EXEC_RESULT}")
endif()

file(READ ${EXPECTED_FILE} EXPECTED_OUTPUT)

# Убираем лишние пробелы и переносы строк в конце для надежности
string(STRIP "${ACTUAL_OUTPUT}" ACTUAL_STRIPPED)
string(STRIP "${EXPECTED_OUTPUT}" EXPECTED_STRIPPED)

if(NOT ACTUAL_STRIPPED STREQUAL EXPECTED_STRIPPED)
    message(FATAL_ERROR "Test failed!\n\nExpected output:\n${EXPECTED_STRIPPED}\n\nActual output:\n${ACTUAL_STRIPPED}")
else()
    message(STATUS "Test passed successfully!")
endif()