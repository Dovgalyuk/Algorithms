cmake_minimum_required(VERSION 3.15)

add_executable(Lab2CPP
    main.cpp
)

target_include_directories(Lab2CPP PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP
)

target_link_libraries(Lab2CPP PRIVATE LibraryCPP)

enable_testing()

add_test(
    NAME Test_StackMachine
    COMMAND bash -lc "$<TARGET_FILE:Lab2CPP> < ${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
)

set_tests_properties(Test_StackMachine PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PASS_REGULAR_EXPRESSION "stack:\n1\nvars:\n5\n0\n0\n0"
    FAIL_REGULAR_EXPRESSION "Error: Argument Error: bipush requires an argument"
)

add_test(
    NAME Test_StackMachine_2
    COMMAND bash -lc "$<TARGET_FILE:Lab2CPP> < ${CMAKE_CURRENT_SOURCE_DIR}/input_2.txt"
)

set_tests_properties(Test_StackMachine_2 PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PASS_REGULAR_EXPRESSION "stack:\n73\nvars:\n100\n10\n99\n0"
    FAIL_REGULAR_EXPRESSION "Error: Stack Error: pop requires at least one value on the stack"
)

add_test(
    NAME Test_StackMachine_3
    COMMAND bash -lc "$<TARGET_FILE:Lab2CPP> < ${CMAKE_CURRENT_SOURCE_DIR}/input_3.txt"
)

set_tests_properties(Test_StackMachine_3 PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PASS_REGULAR_EXPRESSION "stack:\n16\nvars:\n4\n12\n5\n2"
    FAIL_REGULAR_EXPRESSION "Error: Variable Index Error: invalid variable index"
)

add_test(
    NAME Test_StackMachine_4
    COMMAND bash -lc "$<TARGET_FILE:Lab2CPP> < ${CMAKE_CURRENT_SOURCE_DIR}/input_4.txt"
)

set_tests_properties(Test_StackMachine_4 PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PASS_REGULAR_EXPRESSION "Error:"
    FAIL_REGULAR_EXPRESSION "Error: Return Address Error: pop with return address"
)

add_test(
    NAME Test_StackMachine_5
    COMMAND bash -lc "$<TARGET_FILE:Lab2CPP> < ${CMAKE_CURRENT_SOURCE_DIR}/input_5.txt"
)

set_tests_properties(Test_StackMachine_5 PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PASS_REGULAR_EXPRESSION "Error:"
    FAIL_REGULAR_EXPRESSION "Error: Arithmetic Operation Error: Arithmetic operation requires at least two values on the stack"
)

add_test(
    NAME Test_StackMachine_6
    COMMAND bash -lc "$<TARGET_FILE:Lab2CPP> < ${CMAKE_CURRENT_SOURCE_DIR}/input_6.txt"
)

set_tests_properties(Test_StackMachine_6 PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PASS_REGULAR_EXPRESSION "Error:"
    FAIL_REGULAR_EXPRESSION "Error: Call Address Error: invalid call address"
)
