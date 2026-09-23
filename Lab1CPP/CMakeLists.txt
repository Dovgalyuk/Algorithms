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

add_test(NAME task1_test1 COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test1.txt)
set_property(TEST task1_test1 PROPERTY PASS_REGULAR_EXPRESSION "1 1 6 24 120")

add_test(NAME task1_test2 COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test2.txt)
set_property(TEST task1_test2 PROPERTY PASS_REGULAR_EXPRESSION "720")

add_test(NAME task1_test3 COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test3.txt)
set_property(TEST task1_test3 PROPERTY PASS_REGULAR_EXPRESSION "2 2 6 6")

add_test(NAME task1_test4 COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test4.txt)
set_property(TEST task1_test4 PROPERTY WILL_FAIL TRUE)

add_test(NAME task1_test5 COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test5.txt)
set_property(TEST task1_test5 PROPERTY WILL_FAIL TRUE)

add_test(NAME task1_test6 COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test6.txt)
set_property(TEST task1_test6 PROPERTY PASS_REGULAR_EXPRESSION "2 2 24 120")

add_test(NAME task1_test7 COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test7.txt)
set_property(TEST task1_test7 PROPERTY PASS_REGULAR_EXPRESSION "2 720 2 2")

add_test(NAME task2_test1 COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test1.txt)
set_property(TEST task2_test1 PROPERTY PASS_REGULAR_EXPRESSION "2 3 5")

add_test(NAME task2_test2 COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test2.txt)
set_property(TEST task2_test2 PROPERTY PASS_REGULAR_EXPRESSION "7 11 13 17")

add_test(NAME task2_test3 COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test3.txt)
set_property(TEST task2_test3 PROPERTY PASS_REGULAR_EXPRESSION "42")

add_test(NAME task2_test4 COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test4.txt)
set_property(TEST task2_test4 PROPERTY PASS_REGULAR_EXPRESSION "2")

add_test(NAME task2_test5 COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test5.txt)
set_property(TEST task2_test5 PROPERTY WILL_FAIL TRUE)

add_test(NAME task2_test6 COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test6.txt)
set_property(TEST task2_test6 PROPERTY PASS_REGULAR_EXPRESSION "3 5 7")

add_test(NAME task2_test7 COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test7.txt)
set_property(TEST task2_test7 PROPERTY PASS_REGULAR_EXPRESSION "3 2")
