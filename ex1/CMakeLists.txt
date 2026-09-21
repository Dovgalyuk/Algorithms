cmake_minimum_required(VERSION 3.16)

project(CarsProject)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_executable(cars cars.cpp)

add_test(
    NAME CarsTest1
    COMMAND cars ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
)

set_tests_properties(
    CarsTest1
    PROPERTIES PASS_REGULAR_EXPRESSION "2 6"
)

add_test(
    NAME CarsTest2
    COMMAND cars ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
)

set_tests_properties(
    CarsTest2
    PROPERTIES PASS_REGULAR_EXPRESSION "3"
)

add_test(
    NAME CarsTest3
    COMMAND cars ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt
)

set_tests_properties(
    CarsTest3
    PROPERTIES PASS_REGULAR_EXPRESSION "1 2"
)
