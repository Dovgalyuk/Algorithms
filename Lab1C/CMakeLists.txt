cmake_minimum_required(VERSION 3.10)
project(array_processor)

set(CMAKE_C_STANDARD 11)

add_executable(Lab1C lab1.c array.c)

set(TEST_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")

add_test(NAME TestLab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set_property(TEST TestLab1C PROPERTY PASS_REGULAR_EXPRESSION "0 5 8 8 2 3 5 2 9 4
1 2 3 4 5")