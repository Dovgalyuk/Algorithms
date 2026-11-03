add_executable(Lab1C task1.cpp)
target_include_directories(Lab1C PUBLIC ../LibraryCPP)
target_link_libraries(Lab1C LibraryCPP)


add_test(NAME Test1_task COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST Test1_task PROPERTY PASS_REGULAR_EXPRESSION "YES")

add_test(NAME Test2_task COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST Test2_task PROPERTY PASS_REGULAR_EXPRESSION "NO")

add_test(NAME Test3_task COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST Test3_task PROPERTY PASS_REGULAR_EXPRESSION "YES")

add_test(NAME Test4_task COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST Test4_task PROPERTY PASS_REGULAR_EXPRESSION "NO")

add_test(NAME Test_Err_NoBrackets COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input_err1.txt)
set_property(TEST Test_Err_NoBrackets PROPERTY PASS_REGULAR_EXPRESSION "^ERROR")

add_test(NAME Test_Err_EmptyFile COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input_err2.txt)
set_property(TEST Test_Err_EmptyFile PROPERTY PASS_REGULAR_EXPRESSION "^ERROR")

add_test(NAME Test_Err_NoArgs COMMAND Lab1C)
set_property(TEST Test_Err_NoArgs PROPERTY PASS_REGULAR_EXPRESSION "^ERROR")

add_test(NAME Test_Err_FileNotFound COMMAND Lab1C "non_existent_file.txt")
set_property(TEST Test_Err_FileNotFound PROPERTY PASS_REGULAR_EXPRESSION "^ERROR")