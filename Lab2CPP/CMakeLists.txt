add_executable(Lab2CPP main.cpp)

target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)

target_link_libraries(Lab2CPP LibraryCPP)

add_test(
    NAME TestCalculonExample
    COMMAND Lab2CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
)

set_property(
    TEST TestCalculonExample
    PROPERTY PASS_REGULAR_EXPRESSION
    "72 101 108 108 111 44 32 119 114 108 100 33 10"
)

add_test(
    NAME TestCalculonGetSub
    COMMAND Lab2CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/test1_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/test1_input.txt
)

set_property(
    TEST TestCalculonGetSub
    PROPERTY PASS_REGULAR_EXPRESSION "7"
)

add_test(
    NAME TestCalculonArithmetic
    COMMAND Lab2CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/test2_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/test2_input.txt
)

set_property(
    TEST TestCalculonArithmetic
    PROPERTY PASS_REGULAR_EXPRESSION "14"
)

add_test(
    NAME TestCalculonCond
    COMMAND Lab2CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/test3_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/test3_input.txt
)

set_property(
    TEST TestCalculonCond
    PROPERTY PASS_REGULAR_EXPRESSION "42"
)

add_test(
    NAME TestCalculonCondFalse
    COMMAND Lab2CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/test4_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/test4_input.txt
)

set_property(
    TEST TestCalculonCondFalse
    PROPERTY PASS_REGULAR_EXPRESSION "5"
)

add_test(
    NAME TestCalculonRepeat
    COMMAND Lab2CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/test5_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/test5_input.txt
)

set_property(
    TEST TestCalculonRepeat
    PROPERTY PASS_REGULAR_EXPRESSION "9 9 9"
)