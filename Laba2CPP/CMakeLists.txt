add_executable(Laba2CPP processor.cpp)
target_include_directories(Laba2CPP PUBLIC ../LibraryCPPTemplate)

add_test(
    NAME TestLaba2Arithmetic
    COMMAND Laba2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/arithmetic.txt
)
set_property(
    TEST TestLaba2Arithmetic
    PROPERTY PASS_REGULAR_EXPRESSION "^A = 5[\r\n]+B = 20[\r\n]+C = 15[\r\n]+D = 0[\r\n]*$"
)

add_test(
    NAME TestLaba2Registers
    COMMAND Laba2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/registers.txt
)
set_property(
    TEST TestLaba2Registers
    PROPERTY PASS_REGULAR_EXPRESSION "^A = 10[\r\n]+B = 0[\r\n]+C = 0[\r\n]+D = 10[\r\n]*$"
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
    PROPERTY PASS_REGULAR_EXPRESSION "^A = 7[\r\n]+B = 0[\r\n]+C = 0[\r\n]+D = 0[\r\n]*$"
)

add_test(
    NAME TestLaba2Negative
    COMMAND Laba2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/negative.txt
)
set_property(
    TEST TestLaba2Negative
    PROPERTY PASS_REGULAR_EXPRESSION "^A = -13[\r\n]+B = 0[\r\n]+C = 0[\r\n]+D = 0[\r\n]*$"
)

add_test(
    NAME TestLaba2BadPop
    COMMAND Laba2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/bad_pop.txt
)
set_property(
    TEST TestLaba2BadPop
    PROPERTY PASS_REGULAR_EXPRESSION "BAD POP"
)

function(add_laba2_error_test name input expected)
    add_test(NAME ${name} COMMAND Laba2CPP "${CMAKE_CURRENT_SOURCE_DIR}/Tests/${input}")
    set_property(TEST ${name} PROPERTY PASS_REGULAR_EXPRESSION "^${expected}[\r\n]*$")
endfunction()

add_laba2_error_test(TestLaba2PushMissing push_missing.txt "BAD PUSH")
add_laba2_error_test(TestLaba2PushExtra push_extra.txt "BAD PUSH")
add_laba2_error_test(TestLaba2PopMissing pop_missing.txt "BAD POP")
add_laba2_error_test(TestLaba2PopExtra pop_extra.txt "BAD POP")
add_laba2_error_test(TestLaba2AddExtra add_extra.txt "BAD add")
add_laba2_error_test(TestLaba2SubExtra sub_extra.txt "BAD sub")
add_laba2_error_test(TestLaba2MulExtra mul_extra.txt "BAD mul")
add_laba2_error_test(TestLaba2CallExtra call_extra.txt "BAD CALL")
add_laba2_error_test(TestLaba2RetExtra ret_extra.txt "BAD RET")
add_laba2_error_test(TestLaba2InvalidPushRegister push_invalid_register.txt "BAD PUSH")
add_laba2_error_test(TestLaba2InvalidPopRegister pop_invalid_register.txt "BAD POP")
add_laba2_error_test(TestLaba2InvalidNumber invalid_number.txt "BAD PUSH")
add_laba2_error_test(TestLaba2NumberOutOfRange number_out_of_range.txt "BAD PUSH")
add_laba2_error_test(TestLaba2UnknownCommand unknown_command.txt "BAD COMMAND")
add_laba2_error_test(TestLaba2CommandsOnSameLine same_line.txt "BAD PUSH")

add_test(NAME TestLaba2Whitespace COMMAND Laba2CPP "${CMAKE_CURRENT_SOURCE_DIR}/Tests/whitespace.txt")
set_property(TEST TestLaba2Whitespace PROPERTY PASS_REGULAR_EXPRESSION
    "^A = 1[\r\n]+B = 0[\r\n]+C = 0[\r\n]+D = 0[\r\n]*$")
