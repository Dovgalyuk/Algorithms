cmake_minimum_required(VERSION 3.20)

project(Lab2CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab2CPP main.cpp
        main.cpp)

target_link_libraries(Lab2CPP PRIVATE LibraryCPP)

enable_testing()

add_test(
        NAME brackets_test1
        COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_brackets1.txt
)
set_tests_properties(brackets_test1 PROPERTIES PASS_REGULAR_EXPRESSION "^YES")

add_test(
        NAME brackets_test2
        COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_brackets2.txt
)
set_tests_properties(brackets_test2 PROPERTIES PASS_REGULAR_EXPRESSION "^NO")

add_test(
        NAME brackets_test3
        COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_brackets3.txt
)
set_tests_properties(brackets_test3 PROPERTIES PASS_REGULAR_EXPRESSION "^YES")

add_test(
        NAME brackets_test4
        COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_brackets4.txt
)
set_tests_properties(brackets_test4 PROPERTIES PASS_REGULAR_EXPRESSION "^NO")

add_test(
        NAME brackets_test5
        COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_brackets5.txt
)
set_tests_properties(brackets_test5 PROPERTIES PASS_REGULAR_EXPRESSION "^NO")

add_test(
        NAME brackets_test6
        COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_brackets6.txt
)
set_tests_properties(brackets_test6 PROPERTIES PASS_REGULAR_EXPRESSION "^NO")

add_test(
        NAME brackets_test7
        COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_brackets7.txt
)
set_tests_properties(brackets_test7 PROPERTIES PASS_REGULAR_EXPRESSION "^YES")