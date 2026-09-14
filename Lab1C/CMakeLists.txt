cmake_minimum_required(VERSION 3.10)
project(lab_array CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(task1 task1.cpp)
add_executable(task2 task2.cpp)

# Тесты для Задания 4 (task1)
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/input1_1.txt "5\n1 4 3 6 8\n")
add_test(NAME Task1_Test1 COMMAND task1 ${CMAKE_CURRENT_BINARY_DIR}/input1_1.txt)
set_tests_properties(Task1_Test1 PROPERTIES PASS_REGULAR_EXPRESSION "1 3 4")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/input1_2.txt "6\n1 3 10 5 7 9\n")
add_test(NAME Task1_Test2 COMMAND task1 ${CMAKE_CURRENT_BINARY_DIR}/input1_2.txt)
set_tests_properties(Task1_Test2 PROPERTIES PASS_REGULAR_EXPRESSION "2")

# Тесты для Задания 5 (task2)
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/input2_1.txt "5\n10 4 18 3 8\n")
add_test(NAME Task2_Test1 COMMAND task2 ${CMAKE_CURRENT_BINARY_DIR}/input2_1.txt)
set_tests_properties(Task2_Test1 PROPERTIES PASS_REGULAR_EXPRESSION "2")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/input2_2.txt "4\n20 10 50 15\n")
add_test(NAME Task2_Test2 COMMAND task2 ${CMAKE_CURRENT_BINARY_DIR}/input2_2.txt)
set_tests_properties(Task2_Test2 PROPERTIES PASS_REGULAR_EXPRESSION "10")