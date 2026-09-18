cmake_minimum_required(VERSION 3.10)
project(Lab1CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Lab1Common STATIC common.cpp)
target_include_directories(Lab1Common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../LibraryCPP
)
target_link_libraries(Lab1Common LibraryCPP)

add_executable(task1 task1.cpp)
target_link_libraries(task1 Lab1Common)

add_executable(task2 task2.cpp)
target_link_libraries(task2 Lab1Common)

enable_testing()

add_test(NAME Task1_Test1
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test1.txt)
set_property(TEST Task1_Test1 PROPERTY PASS_REGULAR_EXPRESSION "0 0 -9 5")

add_test(NAME Task1_Test2
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test2.txt)
set_property(TEST Task1_Test2 PROPERTY PASS_REGULAR_EXPRESSION "-10 0 0 -3 3")

add_test(NAME Task1_Test3
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test3.txt)
set_property(TEST Task1_Test3 PROPERTY PASS_REGULAR_EXPRESSION "90 -75 15 -100 0 -55")

add_test(NAME Task1_SingleElement
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_single_element.txt)
set_property(TEST Task1_SingleElement PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME Task1_AllPositive
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_all_positive.txt)
set_property(TEST Task1_AllPositive PROPERTY PASS_REGULAR_EXPRESSION "0 10 20 30")

add_test(NAME Task1_AllNegative
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_all_negative.txt)
set_property(TEST Task1_AllNegative PROPERTY PASS_REGULAR_EXPRESSION "0 -10 -20 -30")

add_test(NAME Task1_AllZeros
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_all_zeros.txt)
set_property(TEST Task1_AllZeros PROPERTY PASS_REGULAR_EXPRESSION "0 0 0")

add_test(NAME Task1_MaxInt
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_max_int.txt)
set_property(TEST Task1_MaxInt PROPERTY PASS_REGULAR_EXPRESSION "0 -2147483646 0")

add_test(NAME Task1_SameIndices
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_same_indices.txt)
set_property(TEST Task1_SameIndices PROPERTY PASS_REGULAR_EXPRESSION "30 0 50 -20")

add_test(NAME Task1_InvalidIndex
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_invalid_index.txt)
set_property(TEST Task1_InvalidIndex PROPERTY WILL_FAIL TRUE)

add_test(NAME Task1_InvalidSize
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_invalid_size.txt)
set_property(TEST Task1_InvalidSize PROPERTY WILL_FAIL TRUE)

add_test(NAME Task2_Test1
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test1.txt)
set_property(TEST Task2_Test1 PROPERTY PASS_REGULAR_EXPRESSION "0 0 0 10 20")

add_test(NAME Task2_Test2
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test2.txt)
set_property(TEST Task2_Test2 PROPERTY PASS_REGULAR_EXPRESSION "0 0 0 -5 2 0")

add_test(NAME Task2_Test3
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test3.txt)
set_property(TEST Task2_Test3 PROPERTY PASS_REGULAR_EXPRESSION "0 0 0 0")

add_test(NAME Task2_SingleElement
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_single_element.txt)
set_property(TEST Task2_SingleElement PROPERTY PASS_REGULAR_EXPRESSION "5")

add_test(NAME Task2_ZeroSteps
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_zero_steps.txt)
set_property(TEST Task2_ZeroSteps PROPERTY PASS_REGULAR_EXPRESSION "1 2 3 4 5")

add_test(NAME Task2_FullShift
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_full_shift.txt)
set_property(TEST Task2_FullShift PROPERTY PASS_REGULAR_EXPRESSION "0 0 0 0 0")

add_test(NAME Task2_ShiftMoreThanSize
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_shift_more_than_size.txt)
set_property(TEST Task2_ShiftMoreThanSize PROPERTY PASS_REGULAR_EXPRESSION "0 0 0 0 0")

add_test(NAME Task2_AllZeros
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_all_zeros.txt)
set_property(TEST Task2_AllZeros PROPERTY PASS_REGULAR_EXPRESSION "0 0 0 0")

add_test(NAME Task2_ShiftLeft
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_shift_left.txt)
set_property(TEST Task2_ShiftLeft PROPERTY PASS_REGULAR_EXPRESSION "3 4 5 0 0")

add_test(NAME Task2_ShiftRight
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_shift_right.txt)
set_property(TEST Task2_ShiftRight PROPERTY PASS_REGULAR_EXPRESSION "0 0 1 2 3")

add_test(NAME Task2_InvalidDirection
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_invalid_direction.txt)
set_property(TEST Task2_InvalidDirection PROPERTY WILL_FAIL TRUE)

add_custom_target(test_all
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS task1 task2
    COMMENT "Running all tests..."
)
