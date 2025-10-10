cmake_minimum_required(VERSION 3.5)
project(LAB1C)
set(CMAKE_CXX_STANDARD 20)

add_executable(Lab1C
        lab1.cpp
        ../LibraryCPP/task1.cpp
        ../LibraryCPP/task2.cpp
        ../LibraryCPP/task1.h
        ../LibraryCPP/task2.h
)

target_include_directories(Lab1C PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/input.txt
        COPYONLY)


enable_testing()

add_executable(TestTask1
        ../LibraryCPP/tests/TestTask1.cpp
        ../LibraryCPP/task1.cpp
)

target_include_directories(TestTask1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP)
add_test(NAME TestTask1 COMMAND TestTask1)

add_executable(TestTask2
        ../LibraryCPP/tests/TestTask2.cpp
        ../LibraryCPP/task2.cpp
)
target_include_directories(TestTask2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP)
add_test(NAME TestTask2 COMMAND TestTask2)
