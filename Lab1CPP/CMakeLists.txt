add_executable(Lab1CPP lab1.cpp )
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set_tests_properties(TestLab1CPP PROPERTIES  PASS_REGULAR_EXPRESSION "Факториал: 1 1 2 6 24")