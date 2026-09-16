cmake_minimum_required(VERSION 3.10)
project(SimpleArrayTasks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task1 task1.cpp)
add_executable(task2 task2.cpp)

enable_testing()

add_test(
    NAME grades_test
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grades_input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/grades_output.txt
)
add_test(
    NAME grades_check
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/grades_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grades_expected.txt
)
set_tests_properties(grades_check PROPERTIES DEPENDS grades_test)

add_test(
    NAME grades_test_2
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grades_input_2.txt
            ${CMAKE_CURRENT_BINARY_DIR}/grades_output_2.txt
)
add_test(
    NAME grades_check_2
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/grades_output_2.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grades_expected_2.txt
)
set_tests_properties(grades_check_2 PROPERTIES DEPENDS grades_test_2)

add_test(
    NAME rle_test
    COMMAND task2
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/rle_input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/rle_output.txt
)
add_test(
    NAME rle_check
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/rle_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/rle_expected.txt
)
set_tests_properties(rle_check PROPERTIES DEPENDS rle_test)

add_test(
    NAME rle_test_2
    COMMAND task2
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/rle_input_2.txt
            ${CMAKE_CURRENT_BINARY_DIR}/rle_output_2.txt
)
add_test(
    NAME rle_check_2
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/rle_output_2.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/rle_expected_2.txt
)
set_tests_properties(rle_check_2 PROPERTIES DEPENDS rle_test_2)