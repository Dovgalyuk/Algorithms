add_test(NAME ArrayTest
    COMMAND Lab1 ${CMAKE_CURRENT_SOURCE_DIR}/test_data.txt
)

set_tests_properties(ArrayTest PROPERTIES
    PASS_REGULAR_EXPRESSION "5 8 2 6[ \t\r\n]+-3 -1 -4[ \t\r\n]+2"
)