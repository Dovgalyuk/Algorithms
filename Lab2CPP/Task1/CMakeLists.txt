add_executable(Lab2Task1 main.cpp)

target_include_directories(Lab2Task1 PUBLIC ../../LibraryCPPTemplate)

add_test(NAME Lab2Test1Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/example.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/example.in)
set_property(TEST Lab2Test1Task1 PROPERTY PASS_REGULAR_EXPRESSION "^A\nB\nC\n$")

add_test(NAME Lab2Test2Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/empty_script.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/empty_script.in)
set_property(TEST Lab2Test2Task1 PROPERTY PASS_REGULAR_EXPRESSION "^\n\n\n$")

add_test(NAME Lab2Test3Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/cat.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/cat.in)
set_property(TEST Lab2Test3Task1 PROPERTY PASS_REGULAR_EXPRESSION "^abc\n\n\n\n$")

add_test(NAME Lab2Test4Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/duplicate.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/duplicate.in)
set_property(TEST Lab2Test4Task1 PROPERTY PASS_REGULAR_EXPRESSION "^a\n\na\n$")

add_test(NAME Lab2Test5Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/deduplicate.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/deduplicate.in)
set_property(TEST Lab2Test5Task1 PROPERTY PASS_REGULAR_EXPRESSION "^a\n\n\n\n$")

add_test(NAME Lab2Test6Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/subtract.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/subtract.in)
set_property(TEST Lab2Test6Task1 PROPERTY PASS_REGULAR_EXPRESSION "^\\\\x03\nd\n\n$")

add_test(NAME Lab2Test7Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/move_all.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/move_all.in)
set_property(TEST Lab2Test7Task1 PROPERTY PASS_REGULAR_EXPRESSION "^\n\nCBA\n$")

add_test(NAME Lab2Test8Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/move_between.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/move_between.in)
set_property(TEST Lab2Test8Task1 PROPERTY PASS_REGULAR_EXPRESSION "^\nBA\nC\n$")

add_test(NAME Lab2Test9Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/pop_empty.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/pop_empty.in)
set_property(TEST Lab2Test9Task1 PROPERTY PASS_REGULAR_EXPRESSION "^\n\\\\xff\n\n$")

add_test(NAME Lab2Test10Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/eof_gives_zero.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/eof_gives_zero.in)
set_property(TEST Lab2Test10Task1 PROPERTY PASS_REGULAR_EXPRESSION "^\\\\x00\n\n\n$")

add_test(NAME Lab2Test11Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/error_rule.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/error_rule.in)
set_property(TEST Lab2Test11Task1 PROPERTY PASS_REGULAR_EXPRESSION "Hanoi error: .*rule violated")

add_test(NAME Lab2Test12Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/error_irreversible.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/error_irreversible.in)
set_property(TEST Lab2Test12Task1 PROPERTY PASS_REGULAR_EXPRESSION "Hanoi error: .*irreversible")

add_test(NAME Lab2Test13Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/no_such_file.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/example.in)
set_property(TEST Lab2Test13Task1 PROPERTY PASS_REGULAR_EXPRESSION "cannot open file")

add_test(NAME Lab2Test14Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/big_tower.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/big_tower.in)
set_property(TEST Lab2Test14Task1 PROPERTY PASS_REGULAR_EXPRESSION "^0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\n\n\n\n$")

add_test(NAME Lab2Test15Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/error_rule_tower1.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/error_rule_tower1.in)
set_property(TEST Lab2Test15Task1 PROPERTY PASS_REGULAR_EXPRESSION "Hanoi error: command '\\)' at position 4: .*rule violated")

add_test(NAME Lab2Test16Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/error_rule_tower3.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/error_rule_tower3.in)
set_property(TEST Lab2Test16Task1 PROPERTY PASS_REGULAR_EXPRESSION "Hanoi error: command '\\]' at position 4: .*rule violated")

add_test(NAME Lab2Test17Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/subtract_empty.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/subtract_empty.in)
set_property(TEST Lab2Test17Task1 PROPERTY PASS_REGULAR_EXPRESSION "^\n\\\\xff\\\\x00\n\n$")

add_test(NAME Lab2Test18Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/deduplicate_empty.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/deduplicate_empty.in)
set_property(TEST Lab2Test18Task1 PROPERTY PASS_REGULAR_EXPRESSION "^\n\\\\xff\n\n$")

add_test(NAME Lab2Test19Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/subtract_equal.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/subtract_equal.in)
set_property(TEST Lab2Test19Task1 PROPERTY PASS_REGULAR_EXPRESSION "^\na\\\\x00\n\n$")

add_test(NAME Lab2Test20Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/comments_ignored.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/comments_ignored.in)
set_property(TEST Lab2Test20Task1 PROPERTY PASS_REGULAR_EXPRESSION "^A\nB\nC\n$")

add_test(NAME Lab2Test21Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/crlf_input.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/crlf_input.in)
set_property(TEST Lab2Test21Task1 PROPERTY PASS_REGULAR_EXPRESSION "^ab\n\n\n\n$")

add_test(NAME Lab2Test22Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/utf8_bytes.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/utf8_bytes.in)
set_property(TEST Lab2Test22Task1 PROPERTY PASS_REGULAR_EXPRESSION "^\\\\x8f\n\\\\xd1\n\n$")

add_test(NAME Lab2Test23Task1 COMMAND Lab2Task1)
set_property(TEST Lab2Test23Task1 PROPERTY PASS_REGULAR_EXPRESSION "Usage:")

add_test(NAME Lab2Test24Task1 COMMAND Lab2Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/example.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/no_such_file.in)
set_property(TEST Lab2Test24Task1 PROPERTY PASS_REGULAR_EXPRESSION "cannot open file")
