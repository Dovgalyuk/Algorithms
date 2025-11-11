cmake_minimum_required(VERSION 3.10)
project(Lab2CPP)

add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

enable_testing()

add_test(NAME Test1 COMMAND $<TARGET_FILE:Lab2CPP>
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.in)

set_tests_properties(Test1 PROPERTIES PASS_REGULAR_EXPRESSION
"PUSH 1.*PUSH 2.*PUSH 3.*MUL A, B.*ADD A, B.*PUSH A")

add_test(NAME Test2 COMMAND $<TARGET_FILE:Lab2CPP>
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2.in)

set_tests_properties(Test2 PROPERTIES PASS_REGULAR_EXPRESSION
"PUSH 1.*PUSH 2.*ADD A, B.*PUSH A.*PUSH 3.*MUL A, B.*PUSH A")

add_test(NAME Test4 COMMAND $<TARGET_FILE:Lab2CPP>
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3.in)
set_tests_properties(Test4 PROPERTIES PASS_REGULAR_EXPRESSION
"PUSH 10.*PUSH 2.*SUB A, B.*PUSH A.*PUSH 3.*SUB A, B.*PUSH A")

add_test(NAME Test5 COMMAND $<TARGET_FILE:Lab2CPP>
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test4.in)
set_tests_properties(Test5 PROPERTIES PASS_REGULAR_EXPRESSION
"PUSH 2.*PUSH 3.*ADD A, B.*PUSH A.*PUSH 5.*PUSH 1.*SUB A, B.*PUSH A.*MUL A, B.*PUSH A")


