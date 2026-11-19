execute_process(COMMAND "${PROGRAM}"
    INPUT_FILE "${INPUT}"
    OUTPUT_VARIABLE actual RESULT_VARIABLE status)
file(READ "${EXPECTED}" expected)
if(NOT status STREQUAL "0" OR NOT actual STREQUAL expected)
    message(FATAL_ERROR "Полученный вывод:\n${actual}\nОжидалось:\n${expected}")
endif()
