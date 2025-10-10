cmake_minimum_required(VERSION 3.16)
project(LAB1C)
set(CMAKE_CXX_STANDARD 20)

add_executable(Lab1C
        lab1.cpp
        Function.h
        ../LibraryCPP/task1.cpp
	../LibraryCPP/task2.cpp
        ../LibraryCPP/task1.h
        ../LibraryCPP/task2.h
)

target_include_directories(Lab1C PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP
)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/input.txt
        COPYONLY)


enable_testing()


add_test(NAME TestLab1C COMMAND Lab1C ${CMAKE_CURRENT_BINARY_DIR}/input.txt)

# Проверяем вывод
set_tests_properties(TestLab1C PROPERTIES
        PASS_REGULAR_EXPRESSION
        "размер массива;элементы массива;интервал;Максимальная длина отрезка нечетных чисел;Сжатый массив"
)
