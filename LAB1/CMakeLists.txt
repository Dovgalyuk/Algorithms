cmake_minimum_required(VERSION 4.0)
project(LAB1)

set(CMAKE_CXX_STANDARD 20)

add_executable(LAB1 main.cpp
        Function.h)

enable_testing()

add_test(NAME Run_LAB1 COMMAND LAB1)

set_tests_properties(Run_LAB1 PROPERTIES
        PASS_REGULAR_EXPRESSION "Сжатый"
)