add_executable(Lab1C opz.cpp)
target_include_directories(Lab1C PUBLIC ../LibraryCPP)
target_link_libraries(Lab1C LibraryCPP)

add_test(NAME Test_File_Caps_1 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt)
set_tests_properties(Test_File_Caps_1 PROPERTIES PASS_REGULAR_EXPRESSION "ABC\\*\\+D\\+")

# Т2: A*B+C/D
add_test(NAME Test_File_Caps_2 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt)
set_tests_properties(Test_File_Caps_2 PROPERTIES PASS_REGULAR_EXPRESSION "AB\\*CD/+")

# Т3: A-B-C
add_test(NAME Test_File_Caps_3 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt)
set_tests_properties(Test_File_Caps_3 PROPERTIES PASS_REGULAR_EXPRESSION "AB-C-")

# Т4: A*(B+C)
add_test(NAME Test_File_Caps_4 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test4.txt)
set_tests_properties(Test_File_Caps_4 PROPERTIES PASS_REGULAR_EXPRESSION "ABC\\+\\*")

# Т5: (A+B)/(C-D)
add_test(NAME Test_File_Caps_5 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test5.txt)
set_tests_properties(Test_File_Caps_5 PROPERTIES PASS_REGULAR_EXPRESSION "AB\\+CD-\\/")