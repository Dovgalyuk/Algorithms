cmake_minimum_required(VERSION 3.10)
project(DynamicArrayProject)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_executable(array_program main.cpp)

add_test(NAME Test1 
    COMMAND array_program
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test1
)

add_test(NAME Test2
    COMMAND array_program
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test2
)