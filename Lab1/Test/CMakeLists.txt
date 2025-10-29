add_test(NAME Lab1Test
    COMMAND Lab1
        ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
)

set_tests_properties(Lab1Test PROPERTIES
    PASS_REGULAR_EXPRESSION "5 8 2[ \t\r\n]+-3 -1 -4[ \t\r\n]+2"
)