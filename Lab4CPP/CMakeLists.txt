cmake_minimum_required(VERSION 3.10)
project(Lab4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab4CPP 
    lab4.cpp 
    ${CMAKE_SOURCE_DIR}/LibraryCPPTemplate/Tests/graph.cpp
)

target_include_directories(Lab4CPP PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/LibraryCPPTemplate
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)

add_test(NAME TestLab4CPP COMMAND Lab4CPP)
set_property(TEST TestLab4CPP PROPERTY PASS_REGULAR_EXPRESSION "Testing Graph Library")

add_test(NAME TestLab4CPP_1 COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt A E)
set_property(TEST TestLab4CPP_1 PROPERTY PASS_REGULAR_EXPRESSION "Shortest Paths")