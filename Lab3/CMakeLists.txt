add_executable(Lab3 "lab3.cpp")

target_include_directories(Lab3 PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestLab3Task1 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(TestLab3Task1 PROPERTIES PASS_REGULAR_EXPRESSION "0 5 8 8 2 3 5 2 9 4")

add_test(NAME TestLab3Task2 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(TestLab3Task2 PROPERTIES PASS_REGULAR_EXPRESSION "2")