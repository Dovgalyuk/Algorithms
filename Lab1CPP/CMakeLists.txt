add_executable(grad grad.cpp)

target_include_directories(
        grad
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(nab nab.cpp)

target_include_directories(
        nab
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

enable_testing()

add_test(
        NAME grad_test1
        COMMAND grad ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_grad1.txt
)

set_tests_properties(
        grad_test1
        PROPERTIES
        PASS_REGULAR_EXPRESSION "4 3 2 1"
)

add_test(
        NAME grad_test2
        COMMAND grad ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_grad2.txt
)

set_tests_properties(
        grad_test2
        PROPERTIES
        PASS_REGULAR_EXPRESSION "1 1 0 4"
)

add_test(
        NAME grad_test3
        COMMAND grad ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_grad3.txt
)

set_tests_properties(
        grad_test3
        PROPERTIES
        PASS_REGULAR_EXPRESSION "9 0 0 0"
)

add_test(
        NAME nab_test1
        COMMAND nab ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_nab1.txt
)

set_tests_properties(
        nab_test1
        PROPERTIES
        PASS_REGULAR_EXPRESSION "Самое частое число: 987 \\(встречается 5 раз\\)"
)

add_test(
        NAME nab_test2
        COMMAND nab ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_nab2.txt
)

set_tests_properties(
        nab_test2
        PROPERTIES
        PASS_REGULAR_EXPRESSION "Самое частое число: 666 \\(встречается 2 раз\\)"
)

add_test(
        NAME nab_test3
        COMMAND nab ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_nab3.txt
)

set_tests_properties(
        nab_test3
        PROPERTIES
        PASS_REGULAR_EXPRESSION "Самое частое число: 950 \\(встречается 9 раз\\)"
)
