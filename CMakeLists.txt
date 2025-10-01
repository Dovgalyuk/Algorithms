cmake_minimum_required(VERSION 3.10)
project(arraylab)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab main.cpp)

enable_testing()

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_test(
    NAME Test
    COMMAND ${CMAKE_COMMAND} -E remove ${SRC_DIR}/actual_output.txt
            COMMAND ${CMAKE_COMMAND} -E chdir ${SRC_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Debug/lab.exe < input.txt > actual_output.txt
            COMMAND ${CMAKE_COMMAND} -E compare_files ${SRC_DIR}/expected_output.txt ${SRC_DIR}/actual_output.txt
    WORKING_DIRECTORY ${SRC_DIR}
)