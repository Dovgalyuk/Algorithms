cmake_minimum_required(VERSION 3.10)
project(ArrayProgram)


set(CMAKE_CXX_STANDARD 17)


set(SOURCE_FILES
    labb.cpp
    array.cpp
    array.h
)

add_executable(ArrayProgram ${SOURCE_FILES})


enable_testing()

add_test(
    NAME ArrayProgramTest
    COMMAND ArrayProgram
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}  
)

configure_file(input1.txt ${CMAKE_BINARY_DIR}/input1.txt COPYONLY)
configure_file(input2.txt ${CMAKE_BINARY_DIR}/input2.txt COPYONLY)


