add_executable(Lab1CPPClass main.cpp)
target_include_directories(Lab1CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPPClass LibraryCPPClass)

# Тест для проверки Reverse
add_test(NAME TestLab1CPPClassReverse COMMAND Lab1CPPClass reverse ${CMAKE_CURRENT_SOURCE_DIR}/input_reverse.txt)
set_tests_properties(TestLab1CPPClassReverse PROPERTIES PASS_REGULAR_EXPRESSION "5 4 3 2 1 ")

# Тест для проверки Shift
add_test(NAME TestLab1CPPClassShift COMMAND Lab1CPPClass shift ${CMAKE_CURRENT_SOURCE_DIR}/input_shift.txt l 2)
set_tests_properties(TestLab1CPPClassShift PROPERTIES PASS_REGULAR_EXPRESSION "3 4 5 0 0 ")