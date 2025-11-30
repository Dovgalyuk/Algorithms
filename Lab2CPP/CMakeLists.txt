cmake_minimum_required(VERSION 3.5)
project(LAB2CPP)
set(CMAKE_CXX_STANDARD 20)

add_executable(Lab2CPP
        Lab2.cpp
    ../LibraryCPP/list.cpp
        ../LibraryCPP/stack.cpp
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/input.txt
        COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/script.calc
        ${CMAKE_CURRENT_BINARY_DIR}/script.calc
        COPYONLY)

target_include_directories(Lab2CPP PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP
)

enable_testing()

add_test(NAME TestCalculon
        COMMAND Lab2CPP
        ${CMAKE_CURRENT_BINARY_DIR}/script.calc
        ${CMAKE_CURRENT_BINARY_DIR}/input.txt)

set_tests_properties(TestCalculon PROPERTIES
        PASS_REGULAR_EXPRESSION
        "72 101 108 108 111 44 32 119 114 108 100 33 10"
)