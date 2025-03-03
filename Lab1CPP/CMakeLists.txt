cmake_minimum_required(VERSION 3.10)
project(FixedSizeArrayExample)

set(CMAKE_CXX_STANDARD 17)

add_executable(FixedSizeArrayExample lab1.cpp)

enable_testing()

add_test(
    NAME FixedSizeArrayTest
    COMMAND $<TARGET_FILE:FixedSizeArrayExample>
)

# Example input for the test
set_tests_properties(FixedSizeArrayTest PROPERTIES
    INPUT "10\n15\n"
)
