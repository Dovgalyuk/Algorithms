add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_test(NAME TestLab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test1_input.txt)
set_tests_properties(TestLab3CPP PROPERTIES PASS_REGULAR_EXPRESSION 
"######
#xxxX#
#x####
#xxxY#
######")

add_test(NAME TestLab3CPP_2 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test2_input.txt)
set_tests_properties(TestLab3CPP_2 PROPERTIES PASS_REGULAR_EXPRESSION "IMPOSSIBLE")

add_test(NAME TestLab3CPP_3 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test3_input.txt)
set_tests_properties(TestLab3CPP_3 PROPERTIES PASS_REGULAR_EXPRESSION 
"######
#..xX#
###x##
#..xY#
######")

add_test(NAME TestLab3CPP_4 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test4_input.txt)
set_tests_properties(TestLab3CPP_4 PROPERTIES PASS_REGULAR_EXPRESSION "IMPOSSIBLE")

add_test(NAME TestLab3CPP_5 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test5_input.txt)
set_tests_properties(TestLab3CPP_5 PROPERTIES PASS_REGULAR_EXPRESSION 
"######
#..xX#
#.#x##
#..xY#
######")

add_test(NAME TestLab3CPP_6 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test6_input.txt)
set_tests_properties(TestLab3CPP_6 PROPERTIES PASS_REGULAR_EXPRESSION 
"######
#...X#
#.##x#
#Yxxx#
######")


add_test(NAME TestLab3CPP_7 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test7_input.txt)
set_tests_properties(TestLab3CPP_7 PROPERTIES PASS_REGULAR_EXPRESSION 
"######
#X...#
#x##.#
#Y...#
######")


add_test(NAME TestLab3CPP_8 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test8_input.txt)
set_tests_properties(TestLab3CPP_8 PROPERTIES PASS_REGULAR_EXPRESSION 
"######
#....#
#....#
#YxxX#
######")