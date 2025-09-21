cmake_minimum_required(VERSION 3.10)
project(array_processor)

set(CMAKE_C_STANDARD 11)

add_executable(array_processor lab1.c array.c)

set(TEST_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")

add_test(NAME array_processor_test
         COMMAND array_processor ${TEST_INPUT}
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

set_tests_properties(array_processor_test PROPERTIES
    PASS_REGULAR_EXPRESSION "Task 1 - Digits of 1/17: \\[0, 5, 8, 8, 2, 3, 5, 2, 9, 4, 1, 1, 7, 6, 4, 7, 0, 5, 8, 8\\].*Task 2 - Max sum of 5 consecutive elements: 36"
)