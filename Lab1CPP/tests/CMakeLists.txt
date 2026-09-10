add_test(
    NAME Task4Test1
    COMMAND Task4 ${CMAKE_CURRENT_SOURCE_DIR}/task4_input1.txt
)

set_tests_properties(
    Task4Test1
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Poz: 1 2 3 4 5 6 7 8 9"
)


add_test(
    NAME Task4Test2
    COMMAND Task4 ${CMAKE_CURRENT_SOURCE_DIR}/task4_input2.txt
)

set_tests_properties(
    Task4Test2
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Poz: 2 7 4 8"
)


add_test(
    NAME Task4Test3
    COMMAND Task4 ${CMAKE_CURRENT_SOURCE_DIR}/task4_input3.txt
)

set_tests_properties(
    Task4Test3
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Poz:"
)


add_test(
    NAME Task5Test1
    COMMAND Task5 ${CMAKE_CURRENT_SOURCE_DIR}/task5_input1.txt
)

set_tests_properties(
    Task5Test1
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Max sum: 35"
)


add_test(
    NAME Task5Test2
    COMMAND Task5 ${CMAKE_CURRENT_SOURCE_DIR}/task5_input2.txt
)

set_tests_properties(
    Task5Test2
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Max sum:"
)


add_test(
    NAME Task5Test3
    COMMAND Task5 ${CMAKE_CURRENT_SOURCE_DIR}/task5_input3.txt
)

set_tests_properties(
    Task5Test3
    PROPERTIES
    PASS_REGULAR_EXPRESSION "< 5 int"
)