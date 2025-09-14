add_executable(Lab1CPP lab1.cpp )
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set_tests_properties(TestLab1CPP PROPERTIES PASS_REGULAR_EXPRESSION "Factorial: 1 1 2 6 24 120 720 5040 40320 362880(.|\r|\n)*Maximum sum: 35(.|\r|\n)*Elements with maximum sum: 5 6 7 8 9")
