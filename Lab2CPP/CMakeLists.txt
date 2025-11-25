cmake_minimum_required(VERSION 3.10)
project(Lab2CPP)

set(CMAKE_CXX_STANDARD 11)

# Основная программа - используем существующую библиотеку
add_executable(stack_processor lab2.cpp)
target_include_directories(stack_processor PUBLIC ../LibraryCPP)
target_link_libraries(stack_processor LibraryCPP)

# Тесты
add_test(NAME Test1_BadRet COMMAND stack_processor ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST Test1_BadRet PROPERTY PASS_REGULAR_EXPRESSION "BAD RET")

add_test(NAME Test2_Success COMMAND stack_processor ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST Test2_Success PROPERTY PASS_REGULAR_EXPRESSION "A = 1")

add_test(NAME Test3_Arithmetic COMMAND stack_processor ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST Test3_Arithmetic PROPERTY PASS_REGULAR_EXPRESSION "A = 8")

add_test(NAME Test4_InvalidRet COMMAND stack_processor ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST Test4_InvalidRet PROPERTY PASS_REGULAR_EXPRESSION "BAD RET")

add_test(NAME Test5_Complex COMMAND stack_processor ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST Test5_Complex PROPERTY PASS_REGULAR_EXPRESSION "A = 30")

add_test(NAME Test6_MultipleRegisters COMMAND stack_processor ${CMAKE_CURRENT_SOURCE_DIR}/input6.txt)
set_property(TEST Test6_MultipleRegisters PROPERTY PASS_REGULAR_EXPRESSION "C = 2")

add_test(NAME Test7_CallPop COMMAND stack_processor ${CMAKE_CURRENT_SOURCE_DIR}/input7.txt)
set_property(TEST Test7_CallPop PROPERTY PASS_REGULAR_EXPRESSION "Stack underflow")

add_test(NAME Test8_InvalidCall COMMAND stack_processor ${CMAKE_CURRENT_SOURCE_DIR}/input8.txt)
set_property(TEST Test8_InvalidCall PROPERTY PASS_REGULAR_EXPRESSION "A = 1")