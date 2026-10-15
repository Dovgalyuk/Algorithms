add_executable(Laba2CPP processor.cpp)
target_include_directories(Laba2CPP PUBLIC ../LibraryCPPTemplate)

add_test(
    NAME TestLaba2Arithmetic
    COMMAND Laba2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/arithmetic.txt
)
set_property(
    TEST TestLaba2Arithmetic
    PROPERTY PASS_REGULAR_EXPRESSION "C = 15"
)

add_test(
    NAME TestLaba2Registers
    COMMAND Laba2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/registers.txt
)
set_property(
    TEST TestLaba2Registers
    PROPERTY PASS_REGULAR_EXPRESSION "D = 10"
)

add_test(
    NAME TestLaba2BadRet
    COMMAND Laba2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/bad_ret.txt
)
set_property(
    TEST TestLaba2BadRet
    PROPERTY PASS_REGULAR_EXPRESSION "BAD RET"
)

add_test(
    NAME TestLaba2EmptyRet
    COMMAND Laba2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/empty_ret.txt
)
set_property(
    TEST TestLaba2EmptyRet
    PROPERTY PASS_REGULAR_EXPRESSION "BAD RET"
)

add_test(
    NAME TestLaba2NestedCall
    COMMAND Laba2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/nested_call.txt
)
set_property(
    TEST TestLaba2NestedCall
    PROPERTY PASS_REGULAR_EXPRESSION "A = 7"
)

add_test(
    NAME TestLaba2Negative
    COMMAND Laba2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/negative.txt
)
set_property(
    TEST TestLaba2Negative
    PROPERTY PASS_REGULAR_EXPRESSION "A = -13"
)

add_test(
    NAME TestLaba2BadPop
    COMMAND Laba2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/bad_pop.txt
)
set_property(
    TEST TestLaba2BadPop
    PROPERTY PASS_REGULAR_EXPRESSION "BAD POP"
)
