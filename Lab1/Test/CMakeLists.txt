add_test(NAME ArrayTest1
    COMMAND Lab1 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
)

set_tests_properties(ArrayTest1 PROPERTIES
    PASS_REGULAR_EXPRESSION "5 8 2"
)

add_test(NAME ArrayTest2
    COMMAND Lab1 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
)

set_tests_properties(ArrayTest2 PROPERTIES
    PASS_REGULAR_EXPRESSION "4 4"
)