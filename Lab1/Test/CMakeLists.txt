add_test(NAME ArrayTest_Normal
    COMMAND Lab1 ${CMAKE_CURRENT_SOURCE_DIR}/test_normal.txt
)

set_tests_properties(ArrayTest_Normal PROPERTIES
    PASS_REGULAR_EXPRESSION "5 8 2 6[ \t\r\n]+-3 -1 -4[ \t\r\n]+2"
)

add_test(NAME ArrayTest_SameEvens
    COMMAND Lab1 ${CMAKE_CURRENT_SOURCE_DIR}/test_same_evens.txt
)

set_tests_properties(ArrayTest_SameEvens PROPERTIES
    PASS_REGULAR_EXPRESSION "4 4[ \t\r\n]*[ \t\r\n]*0"
)