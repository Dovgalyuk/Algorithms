cmake_minimum_required(VERSION 3.10)

project(Lab1CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(array_lib
    ../LibraryCPP/array.cpp
)

target_include_directories(array_lib PUBLIC
    ../LibraryCPP
)


add_executable(task1 task1.cpp)
target_link_libraries(task1 array_lib)


add_executable(task2 task2.cpp)
target_link_libraries(task2 array_lib)

enable_testing()

add_test(
    NAME task1_test1
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_1.txt
)

set_tests_properties(task1_test1 PROPERTIES
    PASS_REGULAR_EXPRESSION
    "Первый массив:[ \t]*\n5 8 3 12 7 4 9 6 11 2[ \t]*\nИндексы четных элементов:[ \t]*\n1 3 5 7 9"
)

add_test(
    NAME task1_test2
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_2.txt
)

set_tests_properties(task1_test2 PROPERTIES
    PASS_REGULAR_EXPRESSION
    "Первый массив:[ \t]*\n2 4 6 8 10 12[ \t]*\nИндексы четных элементов:[ \t]*\n0 1 2 3 4 5"
)

add_test(
    NAME task1_test3
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_3.txt
)

set_tests_properties(task1_test3 PROPERTIES
    PASS_REGULAR_EXPRESSION
    "Первый массив:[ \t]*\n1 3 5 7 9[ \t]*\nИндексы четных элементов:"
)


add_test(
    NAME task2_test1
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_1.txt
)

set_tests_properties(task2_test1 PROPERTIES
    PASS_REGULAR_EXPRESSION
    "Элементы, встречающиеся только один раз:[ \t]*\n7 4 6 10"
)

add_test(
    NAME task2_test2
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_2.txt
)

set_tests_properties(task2_test2 PROPERTIES
    PASS_REGULAR_EXPRESSION
    "Элементы, встречающиеся только один раз:[ \t]*\n1 2 3 4 5 6"
)

add_test(
    NAME task2_test3
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_3.txt
)

set_tests_properties(task2_test3 PROPERTIES
    PASS_REGULAR_EXPRESSION
    "Элементы, встречающиеся только один раз:"
)