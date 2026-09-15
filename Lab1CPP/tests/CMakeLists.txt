cmake_minimum_required(VERSION 3.10)
project(lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task1 laba1_task1.cpp)
add_executable(task2 laba1_task2.cpp)

target_include_directories(task1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(task1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

add_test(NAME test1_task1 COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1_1.txt)
set_property(TEST test1_task1 PROPERTY PASS_REGULAR_EXPRESSION "18")

add_test(NAME test2_task1 COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1_2.txt)
set_property(TEST test2_task1 PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME test3_task1 COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1_3.txt)
set_property(TEST test3_task1 PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME test4_task1 COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1_4.txt)
set_property(TEST test4_task1 PROPERTY PASS_REGULAR_EXPRESSION "-3")

add_test(NAME test5_task1 COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1_5.txt)
set_property(TEST test5_task1 PROPERTY PASS_REGULAR_EXPRESSION "0")


add_test(NAME test1_task2 COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2_1.txt)
set_property(TEST test1_task2 PROPERTY PASS_REGULAR_EXPRESSION "5")

add_test(NAME test2_task2 COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2_2.txt)
set_property(TEST test2_task2 PROPERTY PASS_REGULAR_EXPRESSION "100")

add_test(NAME test3_task2 COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2_3.txt)
set_property(TEST test3_task2 PROPERTY PASS_REGULAR_EXPRESIION "1")

add_test(NAME test4_task2 COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2_4.txt)
set_property(TEST test4_task2 PROPERTY PASS_REGULAR_EXPRESSION "7")

add_test(NAME test5_task2 COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2_5.txt)
set_property(TEST test5_task2 PROPERTY PASS_REGULAR_EXPRESSION "0")

add_custom_target(test_all 
	COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --output-on-failure
	DEPENDS task1 task2
	COMMENT "Running all tests..."
)