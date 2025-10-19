cmake_minimum_required(VERSION 3.5)
project(LAB1C)
set(CMAKE_CXX_STANDARD 20)

add_executable(Lab1C
        lab1.cpp
        ../LibraryCPP/task1.cpp
        ../LibraryCPP/task2.cpp
        ../LibraryCPP/array.cpp
)

target_include_directories(Lab1C PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/input.txt
        COPYONLY)


enable_testing()

add_test(NAME TestMaxLength COMMAND Lab1C ${CMAKE_CURRENT_BINARY_DIR}/input.txt)
set_tests_properties(TestMaxLength PROPERTIES
        PASS_REGULAR_EXPRESSION
        "Максимальная длина отрезка нечетных чисел: 1"
)

add_test(NAME TestCompressedArray COMMAND Lab1C ${CMAKE_CURRENT_BINARY_DIR}/input.txt)
set_tests_properties(TestCompressedArray PROPERTIES
        PASS_REGULAR_EXPRESSION
        "Сжатый массив: 5 6 7 8 9 0 0 0 0 0"
)

add_executable(ArrayTest
        ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP/tests/array.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP/array.cpp
)

target_include_directories(ArrayTest PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP
)
