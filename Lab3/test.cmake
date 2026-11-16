execute_process(COMMAND "${PROGRAM}"
    INPUT_FILE "${CMAKE_CURRENT_LIST_DIR}/input.txt"
    OUTPUT_VARIABLE actual RESULT_VARIABLE status)
file(READ "${CMAKE_CURRENT_LIST_DIR}/expected.txt" expected)
if(NOT status STREQUAL "0" OR NOT actual STREQUAL expected)
    message(FATAL_ERROR "Полученный вывод:\n${actual}\nОжидалось:\n${expected}")
endif()
