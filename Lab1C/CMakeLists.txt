add_executable(Lab1C lab1.c)
target_link_libraries(Lab1C PRIVATE LibraryC)

add_test(NAME TestLab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set_tests_properties(TestLab1C PROPERTIES PASS_REGULAR_EXPRESSION
"ќсадки по мес€цам:
1 2 3 4 5 6 7 8 9 10
—жатый массив:
1 6 7 8 9 10 0 0 0 0"
)
