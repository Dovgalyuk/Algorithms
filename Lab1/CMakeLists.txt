add_executable(Lab1 "lab1.cpp")

target_include_directories(Lab1 PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestLab1Task1 COMMAND Lab1 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab1Task1 PROPERTIES PASS_REGULAR_EXPRESSION "0 5 8 8 2 3 5 2 9 4")

add_test(NAME TestLab1Task2 COMMAND Lab1 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab1Task2 PROPERTIES PASS_REGULAR_EXPRESSION "2")