cmake_minimum_required(VERSION 3.15)
project(Lab2Stack)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab2
    lab2.cpp
)

target_include_directories(Lab2 PRIVATE ../LibraryCPPClass)
target_link_libraries(Lab2 PRIVATE LibraryCPPClass)

enable_testing()

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(LAB2_EXE $<TARGET_FILE:Lab2>)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME Test1 COMMAND ${LAB2_EXE} ${TEST_DIR}/test1.txt)
set_tests_properties(Test1 PROPERTIES PASS_REGULAR_EXPRESSION "stack:.*1.*vars:.*5.*0.*0.*0")


add_test(NAME Test2 COMMAND ${LAB2_EXE} ${TEST_DIR}/test2.txt)
set_tests_properties(Test2 PROPERTIES PASS_REGULAR_EXPRESSION "stack:.*vars:.*0.*18.*8.*0")

add_test(NAME Test3 COMMAND ${LAB2_EXE} ${TEST_DIR}/test3.txt)
set_tests_properties(Test3 PROPERTIES PASS_REGULAR_EXPRESSION "stack:.*vars:.*5.*20.*0.*0")

add_test(NAME Test4 COMMAND ${LAB2_EXE} ${TEST_DIR}/test4.txt)
set_tests_properties(Test4 PROPERTIES PASS_REGULAR_EXPRESSION "stack:.*vars:.*8.*7.*4.*0")
