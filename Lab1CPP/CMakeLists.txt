cmake_minimum_required(VERSION 3.10)

project(lab1)

add_library(Array array.cpp)

target_include_directories(Array PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(zadanie1 zadanie1.cpp)
target_link_libraries(zadanie1 Array)

add_executable(zadanie2 zadanie2.cpp)
target_link_libraries(zadanie2 Array)

enable_testing()

add_test(
    NAME Task1_Case1
    COMMAND zadanie1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/input1.txt
)
set_property(TEST Task1_Case1 PROPERTY
    PASS_REGULAR_EXPRESSION "0 5 8 8 2"
)

add_test(
    NAME Task1_Case2
    COMMAND zadanie1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/input2.txt
)
set_property(TEST Task1_Case2 PROPERTY
    PASS_REGULAR_EXPRESSION "0"
)

add_test(
    NAME Task1_Case3
    COMMAND zadanie1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/input3.txt
)
set_property(TEST Task1_Case3 PROPERTY
    PASS_REGULAR_EXPRESSION "0 5 8 8 2 3 5 2 9 4"
)

add_test(
    NAME Task1_Case4
    COMMAND zadanie1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/input4.txt
)
set_property(TEST Task1_Case4 PROPERTY
    PASS_REGULAR_EXPRESSION "0 5 8 8 2 3 5 2 9 4 1 1 7 6 4 7 0"
)

add_test(
    NAME Task1_Case5
    COMMAND zadanie1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/input5.txt
)
set_property(TEST Task1_Case5 PROPERTY
    PASS_REGULAR_EXPRESSION "0 5 8 8 2 3 5 2 9 4 1 1 7 6 4 7 0 5 8 8 2"
)

add_test(
    NAME Task2_Case1
    COMMAND zadanie2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input1.txt
)
set_property(TEST Task2_Case1 PROPERTY
    PASS_REGULAR_EXPRESSION "1 5 30 35 0 0 0 0"
)

add_test(
    NAME Task2_Case2
    COMMAND zadanie2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input2.txt
)
set_property(TEST Task2_Case2 PROPERTY
    PASS_REGULAR_EXPRESSION "1 2 3 4 5"
)

add_test(
    NAME Task2_Case3
    COMMAND zadanie2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input3.txt
)
set_property(TEST Task2_Case3 PROPERTY
    PASS_REGULAR_EXPRESSION "0 0 0 0 0"
)

add_test(
    NAME Task2_Case4
    COMMAND zadanie2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input4.txt
)
set_property(TEST Task2_Case4 PROPERTY
    PASS_REGULAR_EXPRESSION "4 11 0 0 0 0"
)

add_test(
    NAME Task2_Case5
    COMMAND zadanie2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input5.txt
)
set_property(TEST Task2_Case5 PROPERTY
    PASS_REGULAR_EXPRESSION "-10 5 10 0 0 0 0"
)