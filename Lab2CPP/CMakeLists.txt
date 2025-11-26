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


add_test(NAME Test5Err COMMAND ${LAB2_EXE} ${TEST_DIR}/test5err.txt)
set_tests_properties(Test5Err PROPERTIES WILL_FAIL TRUE)

add_test(NAME Test6Err COMMAND ${LAB2_EXE} ${TEST_DIR}/test6err.txt)
set_tests_properties(Test6Err PROPERTIES WILL_FAIL TRUE)

add_test(NAME Test7Err COMMAND ${LAB2_EXE} ${TEST_DIR}/test7err.txt)
set_tests_properties(Test7Err PROPERTIES WILL_FAIL TRUE)

add_test(NAME Test8Err COMMAND ${LAB2_EXE} ${TEST_DIR}/test8err.txt)
set_tests_properties(Test8Err PROPERTIES PASS_REGULAR_EXPRESSION "Unknown operation*")

add_test(NAME Test9Err COMMAND ${LAB2_EXE} ${TEST_DIR}/test9err.txt)
set_tests_properties(Test9Err PROPERTIES PASS_REGULAR_EXPRESSION "Error: return without matching invokestatic\\n?")

add_test(NAME Test10Err COMMAND ${LAB2_EXE} ${TEST_DIR}/test10err.txt)
set_tests_properties(Test10Err PROPERTIES PASS_REGULAR_EXPRESSION "Error: return without matching invokestatic\\n?")

add_test(NAME Test11Err COMMAND ${LAB2_EXE} ${TEST_DIR}/test11err.txt)
set_tests_properties(Test11Err PROPERTIES PASS_REGULAR_EXPRESSION "Error: return without matching invokestatic\\n?")

add_test(NAME Test12 COMMAND ${LAB2_EXE} ${TEST_DIR}/test12.txt)
set_tests_properties(Test12 PROPERTIES PASS_REGULAR_EXPRESSION "Error: invalid stack state before return\\n?")

add_test(NAME Test13 COMMAND ${LAB2_EXE} ${TEST_DIR}/test13err.txt)
set_tests_properties(Test13 PROPERTIES PASS_REGULAR_EXPRESSION "Error: invalid stack state before return\\n?")

add_test(NAME Test14 COMMAND ${LAB2_EXE} ${TEST_DIR}/test14err.txt)
set_tests_properties(Test14 PROPERTIES PASS_REGULAR_EXPRESSION "Error: not enough elements on stack\\n?")

add_test(NAME Test15 COMMAND ${LAB2_EXE} ${TEST_DIR}/test15err.txt)
set_tests_properties(Test15 PROPERTIES PASS_REGULAR_EXPRESSION "Error: empty stack\\n?")