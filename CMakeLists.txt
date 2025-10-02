cmake_minimum_required(VERSION 3.10)
project(arraylab)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab main.cpp)

enable_testing()

set(SRC_DIR ${CMAKE_SOURCE_DIR})

add_test(
    NAME RunArrayTest
    COMMAND sh -c "./array_app < ${SRC_DIR}/input.txt > actual_output.txt && diff ${SRC_DIR}/expected_output.txt actual_output.txt"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}

)
