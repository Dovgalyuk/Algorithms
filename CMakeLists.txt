cmake_minimum_required(VERSION 3.10)
project(DOVprac1)
set(CMAKE_CXX_STANDARD 17)

add_executable(DOVprac1 DOVprac1.cpp testARR.cpp)
target_include_directories(DOVprac1 PRIVATE .)

file(COPY input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

enable_testing()

add_test(NAME run_program
         COMMAND DOVprac1
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set_tests_properties(run_program PROPERTIES
    BYPASS_REGULAR_EXPRESSION "Cannot open input.txt")

add_test(NAME DOVprac1_test
         COMMAND ${CMAKE_COMMAND} -E compare_files
                 ${CMAKE_CURRENT_BINARY_DIR}/output.txt
                 ${CMAKE_CURRENT_SOURCE_DIR}/expected.txt)
set_tests_properties(DOVprac1_test PROPERTIES
    DEPENDS run_program
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})