
cmake_minimum_required(VERSION 3.10)

project(Lab1CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(Lab1CPP lab1.cpp)

target_include_directories(Lab1CPP PUBLIC
    ../LibraryCPP
)

target_link_libraries(Lab1CPP LibraryCPP)



add_test(
    NAME TestLab1CPP
    COMMAND Lab1CPP
            ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
)

set_property(
    TEST TestLab1CPP
    PROPERTY PASS_REGULAR_EXPRESSION
    "Even indices: 1 3 5 7 9"
)



file(WRITE
    ${CMAKE_CURRENT_BINARY_DIR}/input_test2.txt
    "7\n10 11 12 13 14 15 16\n"
)

add_test(
    NAME TestEven2
    COMMAND Lab1CPP
            ${CMAKE_CURRENT_BINARY_DIR}/input_test2.txt
)

set_property(
    TEST TestEven2
    PROPERTY PASS_REGULAR_EXPRESSION
    "Even indices: 0 2 4 6"
)



file(WRITE
    ${CMAKE_CURRENT_BINARY_DIR}/input_test3.txt
    "10\n1 2 3 2 4 1 5 6 6 7\n"
)

add_test(
    NAME TestUnique
    COMMAND Lab1CPP
            ${CMAKE_CURRENT_BINARY_DIR}/input_test3.txt
)

set_property(
    TEST TestUnique
    PROPERTY PASS_REGULAR_EXPRESSION
    "Unique elements: 3 4 5 7"
)

