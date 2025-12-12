cmake_minimum_required(VERSION 3.10)
project(Lab4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab4Program lab4.cpp)

target_include_directories(Lab4Program PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPPTemplate
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input2.txt ${CMAKE_CURRENT_BINARY_DIR}/input2.txt COPYONLY)

add_test(NAME TestLab4CPP_SinglePath COMMAND Lab4Program ${CMAKE_CURRENT_BINARY_DIR}/input.txt A E)
set_property(TEST TestLab4CPP_SinglePath PROPERTY PASS_REGULAR_EXPRESSION "Shortest Paths from A to E.*Path 1:.*A -> C -> E")

add_test(NAME TestLab4CPP_MultiplePaths COMMAND Lab4Program ${CMAKE_CURRENT_BINARY_DIR}/input2.txt A D)
set_property(TEST TestLab4CPP_MultiplePaths PROPERTY PASS_REGULAR_EXPRESSION "Shortest Paths from A to D.*Path 1:.*A -> B -> D.*Path 2:.*A -> C -> D")