cmake_minimum_required(VERSION 3.10)
project(Lab1C)

add_executable(TestLab1C lab1.c array.c)

add_test(NAME TestLab1C 
    COMMAND TestLab1C input
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)