add_executable(Lab4 "lab4.cpp")

target_include_directories(Lab4 PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestLab4Test1 COMMAND Lab4 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(TestLab4Test1 PROPERTIES PASS_REGULAR_EXPRESSION "6")

add_test(NAME TestLab4Test2 COMMAND Lab4 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(TestLab4Test2 PROPERTIES PASS_REGULAR_EXPRESSION "4")