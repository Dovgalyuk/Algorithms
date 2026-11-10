add_executable(Lab1C graf.cpp)
target_include_directories(Lab1C PUBLIC ../LibraryCPP)
target_link_libraries(Lab1C LibraryCPP)

add_test(NAME Test_File_1 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt)
set_tests_properties(Test_File_1 PROPERTIES PASS_REGULAR_EXPRESSION "2")

add_test(NAME Test_File_2 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt)
set_tests_properties(Test_File_2 PROPERTIES PASS_REGULAR_EXPRESSION "2")

add_test(NAME Test_File_3 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt)
set_tests_properties(Test_File_3 PROPERTIES PASS_REGULAR_EXPRESSION "0")

# тесты с IMPOSSIBLE

add_test(NAME Test_Impossible_1 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test4.txt)
set_tests_properties(Test_Impossible_1 PROPERTIES PASS_REGULAR_EXPRESSION "IMPOSSIBLE")

add_test(NAME Test_Impossible_2 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test5.txt)
set_tests_properties(Test_Impossible_2 PROPERTIES PASS_REGULAR_EXPRESSION "IMPOSSIBLE")

# тесты с Error

add_test(NAME Test_Error_Size COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test6.txt)
set_tests_properties(Test_Error_Size PROPERTIES PASS_REGULAR_EXPRESSION "Error")

add_test(NAME Test_Error_Vertex COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test7.txt)
set_tests_properties(Test_Error_Vertex PROPERTIES PASS_REGULAR_EXPRESSION "Error")

add_test(NAME Test_Error_Matrix COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test8.txt)
set_tests_properties(Test_Error_Matrix PROPERTIES PASS_REGULAR_EXPRESSION "Error")

add_test(NAME Test_Error_Letters COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test9.txt)
set_tests_properties(Test_Error_Letters PROPERTIES PASS_REGULAR_EXPRESSION "Error")

add_test(NAME Test_Error_Empty COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test10.txt)
set_tests_properties(Test_Error_Empty PROPERTIES PASS_REGULAR_EXPRESSION "Error")

add_test(NAME Test_Error_NoFile COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/no_such_file.txt)
set_tests_properties(Test_Error_NoFile PROPERTIES PASS_REGULAR_EXPRESSION "Error")