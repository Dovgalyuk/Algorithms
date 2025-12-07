add_executable(Lab3 "lab3.cpp")

target_include_directories(Lab3 PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestLab3Test1 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(TestLab3Test1 PROPERTIES PASS_REGULAR_EXPRESSION "4")

add_test(NAME TestLab3Test2 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(TestLab3Test2 PROPERTIES PASS_REGULAR_EXPRESSION "9")