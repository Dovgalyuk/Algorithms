
cmake_minimum_required(VERSION 3.14)

project(Lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(Lab1C
    lab1.cpp
    array.cpp
    array.h
)

add_test(
    NAME TestLab1
    COMMAND Lab1C
)

set_property(
    TEST TestLab1
    PROPERTY WORKING_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_property(
    TEST TestLab1
    PROPERTY PASS_REGULAR_EXPRESSION
    "Task 1:[ \t\r\n]+2 3 5 7 0 0 0 0 0 0[ \t\r\n]+Task 2:[ \t\r\n]+2"
)

