cmake_minimum_required(VERSION 3.10)
project(Lab3CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../LibraryCPP/Tests ${CMAKE_BINARY_DIR}/LibraryCPP_Tests)

add_executable(conapp main.cpp)
target_include_directories(conapp PUBLIC ../LibraryCPP)
target_link_libraries(conapp PRIVATE LibraryCPP)

enable_testing()

add_test(NAME test1
    COMMAND conapp
        ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt
)
set_property(TEST test1 PROPERTY
    PASS_REGULAR_EXPRESSION "B\nC")


add_test(NAME test2
    COMMAND conapp
        ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt
)
set_property(TEST test2 PROPERTY
    PASS_REGULAR_EXPRESSION "C\nD")


add_test(NAME test3
    COMMAND conapp
        ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt
)
set_property(TEST test3 PROPERTY
    PASS_REGULAR_EXPRESSION "B\nC")


add_test(NAME test4
    COMMAND conapp
        ${CMAKE_CURRENT_SOURCE_DIR}/test4.txt
)
set_property(TEST test4 PROPERTY
    PASS_REGULAR_EXPRESSION "A\nI\nH\nP")


add_test(NAME test5
    COMMAND conapp
        ${CMAKE_CURRENT_SOURCE_DIR}/test5.txt
)
set_property(TEST test5 PROPERTY
    PASS_REGULAR_EXPRESSION "")