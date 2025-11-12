cmake_minimum_required(VERSION 3.10)
project(Lab4CPP)

set(CMAKE_CXX_STANDARD 11)

add_executable(Lab4CPP lab4.cpp)

target_include_directories(Lab4CPP PRIVATE 
    .
    ../LibraryCPPTemplate
)

enable_testing()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)

add_test(NAME TestLab4CPP COMMAND Lab4CPP ${CMAKE_CURRENT_BINARY_DIR}/input.txt)
set_tests_properties(TestLab4CPP PROPERTIES PASS_REGULAR_EXPRESSION "16")