cmake_minimum_required(VERSION 3.10)
project(ConsoleApplication2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(ConsoleApplication2 ConsoleApplication2.cpp)
configure_file(input1.txt input1.txt COPYONLY)
configure_file(input2.txt input2.txt COPYONLY)
configure_file(input.txt input.txt COPYONLY)
enable_testing()
add_test(NAME TestArrayC
    COMMAND ConsoleApplication2 ${CMAKE_CURRENT_BINARY_DIR}/input1.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
add_test(NAME TestLab1C
    COMMAND ConsoleApplication2 ${CMAKE_CURRENT_BINARY_DIR}/input.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
set_property(TEST TestArrayC PROPERTY PASS_REGULAR_EXPRESSION "0 1 2 3 4 5 6 7 8 9")
set_property(TEST TestLab1C PROPERTY PASS_REGULAR_EXPRESSION "1 2 3 4 5")
