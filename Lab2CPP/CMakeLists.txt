add_executable(Lab2CPP lab2.cpp )
target_link_libraries(Lab2CPP LibraryCPP)

add_test(NAME TestLab2CPP_1 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(TestLab2CPP_1 PROPERTIES PASS_REGULAR_EXPRESSION "BAD RET")

add_test(NAME TestLab2CPP_2 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(TestLab2CPP_2 PROPERTIES PASS_REGULAR_EXPRESSION "A = 1.*B = 0.*C = 0.*D = 0")

add_test(NAME TestLab2CPP_3 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_tests_properties(TestLab2CPP_3 PROPERTIES PASS_REGULAR_EXPRESSION "A = 30.*B = 0.*C = 0.*D = 0")

add_test(NAME TestLab2CPP_4 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_tests_properties(TestLab2CPP_4 PROPERTIES PASS_REGULAR_EXPRESSION "BAD POP")


add_test(NAME TestLab2CPP_5 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_tests_properties(TestLab2CPP_5 PROPERTIES PASS_REGULAR_EXPRESSION "A = 0.*B = 0.*C = 0.*D = 0")