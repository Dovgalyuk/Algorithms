cmake_minimum_required(VERSION 3.10)
project(ConsoleApplication2)

set(CMAKE_CXX_STANDARD 11)

add_executable(array_container ConsoleApplication2.cpp)

add_test(NAME TestPalindromes COMMAND array_container ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestPalindromes PROPERTY PASS_REGULAR_EXPRESSION "Массив палиндромов: 0 1 2 3 4 5 6 7 8 9")

add_test(NAME TestEvenDiff COMMAND array_container ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestEvenDiff PROPERTY PASS_REGULAR_EXPRESSION "Минимальная разность четных элементов: 2")