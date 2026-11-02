add_executable(processor processor.cpp)

target_include_directories(processor PUBLIC ../LibraryCPP)

target_link_libraries(processor LibraryCPP)

enable_testing()

add_test(
    NAME ProcessorTest1
    COMMAND processor ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1.txt
)

set_tests_properties(ProcessorTest1 PROPERTIES
    PASS_REGULAR_EXPRESSION "A = 15"
)

add_test(
    NAME ProcessorTest2
    COMMAND processor ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2.txt
)

set_tests_properties(ProcessorTest2 PROPERTIES
    PASS_REGULAR_EXPRESSION "C = 100"
)

add_test(
    NAME ProcessorTest3
    COMMAND processor ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test3.txt
)

set_tests_properties(ProcessorTest3 PROPERTIES
    PASS_REGULAR_EXPRESSION "BAD RET"
)

add_test(
    NAME ProcessorTest4
    COMMAND processor ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test4.txt
)

set_tests_properties(ProcessorTest4 PROPERTIES
    PASS_REGULAR_EXPRESSION "BAD POP"
)

add_test(
    NAME ProcessorTest5
    COMMAND processor ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test5.txt
)

set_tests_properties(ProcessorTest5 PROPERTIES
    PASS_REGULAR_EXPRESSION "A = 15"
)

add_test(
    NAME ProcessorTest6
    COMMAND processor ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test6.txt
)

set_tests_properties(ProcessorTest6 PROPERTIES
    PASS_REGULAR_EXPRESSION "A = 15"
)

add_test(
    NAME ProcessorTest7
    COMMAND processor ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test7.txt
)

set_tests_properties(ProcessorTest7 PROPERTIES
    PASS_REGULAR_EXPRESSION "BAD CALL"
)

add_test(
    NAME ProcessorTest8
    COMMAND processor ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test8.txt
)

set_tests_properties(ProcessorTest8 PROPERTIES
    PASS_REGULAR_EXPRESSION "B = 50"
)

add_test(
    NAME ProcessorTest9
    COMMAND processor ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test9.txt
)

set_tests_properties(ProcessorTest9 PROPERTIES
    PASS_REGULAR_EXPRESSION "A = 12"
)

add_test(
    NAME ProcessorTest10
    COMMAND processor ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test10.txt
)

set_tests_properties(ProcessorTest10 PROPERTIES
    PASS_REGULAR_EXPRESSION "B = 24"
)

add_test(
    NAME ProcessorTest11
    COMMAND processor ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test11.txt
)

set_tests_properties(ProcessorTest11 PROPERTIES
    PASS_REGULAR_EXPRESSION "BAD POP"
)

add_test(
    NAME ProcessorTest12
    COMMAND processor ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test12.txt
)

set_tests_properties(ProcessorTest12 PROPERTIES
    PASS_REGULAR_EXPRESSION "BAD OPERATION"
)

add_test(
    NAME ProcessorTest13
    COMMAND processor ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test13.txt
)

set_tests_properties(ProcessorTest13 PROPERTIES
    PASS_REGULAR_EXPRESSION "BAD RET"
)

add_test(
    NAME ProcessorTest14
    COMMAND processor ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test14.txt
)

set_tests_properties(ProcessorTest14 PROPERTIES
    PASS_REGULAR_EXPRESSION "BAD PUSH"
)

add_test(
    NAME ProcessorTest15
    COMMAND processor ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test15.txt
)

set_tests_properties(ProcessorTest15 PROPERTIES
    PASS_REGULAR_EXPRESSION "BAD COMMAND"
)