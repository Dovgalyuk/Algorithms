cmake_minimum_required(VERSION 3.16)

project(ElementsProject)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_executable(elements elements.cpp)

add_test(
    NAME ElementsTest1
    COMMAND elements ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
)

set_tests_properties(
    ElementsTest1
    PROPERTIES PASS_REGULAR_EXPRESSION "2 3 7"
)

add_test(
    NAME ElementsTest2
    COMMAND elements ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
)

set_tests_properties(
    ElementsTest2
    PROPERTIES PASS_REGULAR_EXPRESSION "3 7"
)

add_test(
    NAME ElementsTest3
    COMMAND elements ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt
)

set_tests_properties(
    ElementsTest3
    PROPERTIES PASS_REGULAR_EXPRESSION "3 5 7 11 13"
)
