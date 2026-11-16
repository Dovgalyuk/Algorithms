# Пример из задания: ответ 4
add_test(NAME Lab3CPP_Task_Example
         COMMAND task ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(Lab3CPP_Task_Example PROPERTIES
    PASS_REGULAR_EXPRESSION "4"
    TIMEOUT 10)

# Два финиша, ближайший — 1
add_test(NAME Lab3CPP_Task_TwoFinishes
         COMMAND task ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(Lab3CPP_Task_TwoFinishes PROPERTIES
    PASS_REGULAR_EXPRESSION "1"
    TIMEOUT 10)

# Финиш недостижим
add_test(NAME Lab3CPP_Task_NoPath
         COMMAND task ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_tests_properties(Lab3CPP_Task_NoPath PROPERTIES
    PASS_REGULAR_EXPRESSION "No path"
    TIMEOUT 10)