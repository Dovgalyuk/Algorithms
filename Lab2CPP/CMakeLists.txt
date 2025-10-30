add_executable(Lab2CPP 
    lab2.cpp 
    ../LibraryCPP/stack.cpp
    ../LibraryCPP/list.cpp
)

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