add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_test(NAME TestLab2CPP_Input1 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab2CPP_Input1 PROPERTIES PASS_REGULAR_EXPRESSION "ABC[*]\\+D\\+")

add_test(NAME TestLab2CPP_Input2 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(TestLab2CPP_Input2 PROPERTIES PASS_REGULAR_EXPRESSION "AB[*]C\\+")

add_test(NAME TestLab2CPP_Input3 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(TestLab2CPP_Input3 PROPERTIES PASS_REGULAR_EXPRESSION "ABCD[+][*]\\+")

add_test(NAME TestLab2CPP_Input4 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_tests_properties(TestLab2CPP_Input4 PROPERTIES PASS_REGULAR_EXPRESSION "AB\\+")

add_test(NAME TestLab2CPP_Input5 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_tests_properties(TestLab2CPP_Input5 PROPERTIES PASS_REGULAR_EXPRESSION "AB\\+C[*]")