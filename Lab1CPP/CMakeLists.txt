add_executable(Task1 task1.cpp)
target_include_directories(Task1 PUBLIC ../LibraryCPP)
target_link_libraries(Task1 LibraryCPP)

add_executable(Task2 task2.cpp)
target_include_directories(Task2 PUBLIC ../LibraryCPP)
target_link_libraries(Task2 LibraryCPP)

add_test(NAME TestTask1_1 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_input.txt)
set_property(TEST TestTask1_1 PROPERTY PASS_REGULAR_EXPRESSION "Avg =4.5" "1 2 3 4 0")

add_test(NAME TestTask1_2 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_input2.txt)
set_property(TEST TestTask1_2 PROPERTY PASS_REGULAR_EXPRESSION "Avg =0" "-5 -10")

add_test(NAME TestTask1_3 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_input3.txt)
set_property(TEST TestTask1_3 PROPERTY PASS_REGULAR_EXPRESSION "Avg =4" "1 3")

add_test(NAME TestTask2_1 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_input.txt)
set_property(TEST TestTask2_1 PROPERTY PASS_REGULAR_EXPRESSION "минимальная разность:2")

add_test(NAME TestTask2_2 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_input2.txt)
set_property(TEST TestTask2_2 PROPERTY PASS_REGULAR_EXPRESSION "минимальная разность:2")

add_test(NAME TestTask2_3 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_input3.txt)
set_property(TEST TestTask2_3 PROPERTY PASS_REGULAR_EXPRESSION "четных нет")
