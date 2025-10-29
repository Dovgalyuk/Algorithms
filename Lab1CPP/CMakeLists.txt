cmake_minimum_required(VERSION 3.5)
project(LAB1CPP)
set(CMAKE_CXX_STANDARD 20)

add_executable(Lab1CPP
        lab1.cpp
        ../LibraryCPP/task1.cpp
        ../LibraryCPP/task2.cpp
        ../LibraryCPP/array.cpp
)

target_include_directories(Lab1CPP PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
        ${CMAKE_CURRENT_BINARY_DIR}/input1.txt
        COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
        ${CMAKE_CURRENT_BINARY_DIR}/input2.txt
        COPYONLY)


enable_testing()

add_test(NAME TestMaxLength1 COMMAND Lab1CPP ${CMAKE_CURRENT_BINARY_DIR}/input1.txt)
set_tests_properties(TestMaxLength1 PROPERTIES
        PASS_REGULAR_EXPRESSION
        "1"
)

add_test(NAME TestCompressedArray1 COMMAND Lab1CPP ${CMAKE_CURRENT_BINARY_DIR}/input1.txt)
set_tests_properties(TestCompressedArray1 PROPERTIES
        PASS_REGULAR_EXPRESSION
        "5 6 7 8 9 0 0 0 0 0"
)

add_test(NAME TestMaxLength2 COMMAND Lab1CPP ${CMAKE_CURRENT_BINARY_DIR}/input2.txt)
set_tests_properties(TestMaxLength2 PROPERTIES
        PASS_REGULAR_EXPRESSION
        "1"
)

add_test(NAME TestCompressedArray2 COMMAND Lab1CPP ${CMAKE_CURRENT_BINARY_DIR}/input2.txt)
set_tests_properties(TestCompressedArray2 PROPERTIES
        PASS_REGULAR_EXPRESSION
        "11 12 13 14 0 0 0 0 0 0"
)


