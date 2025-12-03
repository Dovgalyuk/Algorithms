cmake_minimum_required(VERSION 3.10)
project(Lab4CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab4CPP 
    ${CMAKE_CURRENT_SOURCE_DIR}/lab4.cpp
    ${CMAKE_SOURCE_DIR}/LibraryCPPTemplate/Tests/graph.cpp
)

target_include_directories(Lab4CPP PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/LibraryCPPTemplate
)

target_compile_definitions(Lab4CPP PRIVATE -DNO_GRAPH_MAIN)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/Lab4CPP/input.txt COPYONLY)


add_test(NAME TestLab4CPP COMMAND $<TARGET_FILE:Lab4CPP>)
set_property(TEST TestLab4CPP PROPERTY PASS_REGULAR_EXPRESSION 
    "Testing Graph Library|Vertex count|Has edge"
)

add_test(NAME TestLab4CPP_Paths COMMAND $<TARGET_FILE:Lab4CPP> input.txt A E)
set_property(TEST TestLab4CPP_Paths PROPERTY PASS_REGULAR_EXPRESSION 
    "Shortest Paths|Path.*A.*->.*C.*->.*E|Length: 2"
)