cmake_minimum_required(VERSION 3.10)
project(Lab1CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Lab1Apfelbaum STATIC apfel.cpp)
target_include_directories(Lab1Apfelbaum PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP
)
target_link_libraries(Lab1Apfelbaum LibraryCPP)

add_executable(task1 task1.cpp)
target_link_libraries(task1 Lab1Apfelbaum)

add_executable(task2 task2.cpp)
target_link_libraries(task2 Lab1Apfelbaum)

enable_testing()

file(GLOB TASK1_TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_*.txt")
foreach(TEST_FILE ${TASK1_TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_test(NAME "${TEST_NAME}" COMMAND task1 "${TEST_FILE}")
endforeach()

set_property(TEST task1_test1 PROPERTY PASS_REGULAR_EXPRESSION "1 1 6 24 120")
set_property(TEST task1_test2 PROPERTY PASS_REGULAR_EXPRESSION "720")
set_property(TEST task1_test3 PROPERTY PASS_REGULAR_EXPRESSION "2 2 6 6")
set_property(TEST task1_test4 PROPERTY WILL_FAIL TRUE)
set_property(TEST task1_test5 PROPERTY WILL_FAIL TRUE)

file(GLOB TASK2_TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_*.txt")
foreach(TEST_FILE ${TASK2_TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_test(NAME "${TEST_NAME}" COMMAND task2 "${TEST_FILE}")
endforeach()

set_property(TEST task2_test1 PROPERTY PASS_REGULAR_EXPRESSION "2 3 5")
set_property(TEST task2_test2 PROPERTY PASS_REGULAR_EXPRESSION "7 11 13 17")
set_property(TEST task2_test3 PROPERTY PASS_REGULAR_EXPRESSION "42")
set_property(TEST task2_test4 PROPERTY PASS_REGULAR_EXPRESSION "2")
set_property(TEST task2_test5 PROPERTY WILL_FAIL TRUE)