add_executable(Lab2CPP lab2.cpp)
target_link_libraries(Lab2CPP LibraryCPP)

target_include_directories(Lab2CPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../LibraryCPP)

add_test(NAME TestLab2CPP_1 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(TestLab2CPP_1 PROPERTIES PASS_REGULAR_EXPRESSION "Result: 6")

add_test(NAME TestLab2CPP_2 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(TestLab2CPP_2 PROPERTIES PASS_REGULAR_EXPRESSION "Result: 5")

add_test(NAME TestLab2CPP_3 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_tests_properties(TestLab2CPP_3 PROPERTIES PASS_REGULAR_EXPRESSION "Result: 9")

add_test(NAME TestLab2CPP_4 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_tests_properties(TestLab2CPP_4 PROPERTIES PASS_REGULAR_EXPRESSION "Result: 16")

add_test(NAME TestLab2CPP_5 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_tests_properties(TestLab2CPP_5 PROPERTIES PASS_REGULAR_EXPRESSION "Result: 28")

add_test(NAME TestLab2CPP_6 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input6.txt)
set_tests_properties(TestLab2CPP_6 PROPERTIES PASS_REGULAR_EXPRESSION "Result: 19")

add_test(NAME TestLab2CPP_Error_DivZero COMMAND Lab2CPP input_error1.txt)
set_tests_properties(TestLab2CPP_Error_DivZero PROPERTIES WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PASS_REGULAR_EXPRESSION "Error: Division by zero")

add_test(NAME TestLab2CPP_Error_ParenOpen COMMAND Lab2CPP input_error2.txt)
set_tests_properties(TestLab2CPP_Error_ParenOpen PROPERTIES WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PASS_REGULAR_EXPRESSION "Error: Mismatched parentheses")

add_test(NAME TestLab2CPP_Error_InvalidExpr COMMAND Lab2CPP input_error3.txt)
set_tests_properties(TestLab2CPP_Error_InvalidExpr PROPERTIES WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PASS_REGULAR_EXPRESSION "Error: Invalid expression")
