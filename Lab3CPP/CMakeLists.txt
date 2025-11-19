cmake_minimum_required(VERSION 3.10)
project(Lab3CPP)

add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

enable_testing()

add_test(NAME Test1 COMMAND $<TARGET_FILE:Lab3CPP>
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.in)

set_tests_properties(Test1 PROPERTIES PASS_REGULAR_EXPRESSION
"2")

add_test(NAME Test2 COMMAND $<TARGET_FILE:Lab3CPP>
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2.in)

set_tests_properties(Test2 PROPERTIES PASS_REGULAR_EXPRESSION
"IMPOSSIBLE")

add_test(NAME Test3 COMMAND $<TARGET_FILE:Lab3CPP>
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3.in)
set_tests_properties(Test3 PROPERTIES PASS_REGULAR_EXPRESSION
"1")




