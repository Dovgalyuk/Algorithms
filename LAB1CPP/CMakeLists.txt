add_executable(Fibonachi fibonachi.cpp)
target_include_directories(Fibonachi PRIVATE ../LibraryCPP)
target_link_libraries(Fibonachi PRIVATE LibraryCPP)

add_test(
    NAME TestFibonachi1
    COMMAND Fibonachi ${CMAKE_CURRENT_SOURCE_DIR}/tests/fibonachi_1.txt
)
set_tests_properties(TestFibonachi1 PROPERTIES
    PASS_REGULAR_EXPRESSION "^0[\r\n]*$"
)

add_test(
    NAME TestFibonachi5
    COMMAND Fibonachi ${CMAKE_CURRENT_SOURCE_DIR}/tests/fibonachi_5.txt
)
set_tests_properties(TestFibonachi5 PROPERTIES
    PASS_REGULAR_EXPRESSION "^0 1 1 2 3[\r\n]*$"
)

add_test(
    NAME TestFibonachi10
    COMMAND Fibonachi ${CMAKE_CURRENT_SOURCE_DIR}/tests/fibonachi_10.txt
)
set_tests_properties(TestFibonachi10 PROPERTIES
    PASS_REGULAR_EXPRESSION "^0 1 1 2 3 5 8 13 21 34[\r\n]*$"
)


add_executable(Devide devide.cpp)
target_include_directories(Devide PRIVATE ../LibraryCPP)
target_link_libraries(Devide PRIVATE LibraryCPP)

add_test(
    NAME TestDevideDifferent
    COMMAND Devide ${CMAKE_CURRENT_SOURCE_DIR}/tests/devide_diff.txt
)
set_tests_properties(TestDevideDifferent PROPERTIES
    PASS_REGULAR_EXPRESSION "^2 3 5[\r\n]*$"
)

add_test(
    NAME TestDevideMultiples
    COMMAND Devide ${CMAKE_CURRENT_SOURCE_DIR}/tests/devide_mult.txt
)
set_tests_properties(TestDevideMultiples PROPERTIES
    PASS_REGULAR_EXPRESSION "^2[\r\n]*$"
)

add_test(
    NAME TestDevidePrimes
    COMMAND Devide ${CMAKE_CURRENT_SOURCE_DIR}/tests/devide_prim.txt
)
set_tests_properties(TestDevidePrimes PROPERTIES
    PASS_REGULAR_EXPRESSION "^3 5 7 11[\r\n]*$"
)

