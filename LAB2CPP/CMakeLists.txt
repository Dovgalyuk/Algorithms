add_executable(Lab2CPP main.cpp )
target_include_directories(Lab2CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPP LibraryCPPClass)

add_test(NAME Test_input COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST Test_input PROPERTY PASS_REGULAR_EXPRESSION "YES")

add_test(NAME Test_1_yes COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test_input_1_YES.txt)
set_property(TEST Test_1_yes PROPERTY PASS_REGULAR_EXPRESSION "YES")

add_test(NAME Test_2_NO COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test_input_3_NO.txt)
set_property(TEST Test_2_NO PROPERTY PASS_REGULAR_EXPRESSION "NO")

add_test(NAME Test_4_NO COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test_input_4_NO.txt)
set_property(TEST Test_4_NO PROPERTY PASS_REGULAR_EXPRESSION "NO")

add_test(NAME Test_5_NO COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test_input_5_NO.txt)
set_property(TEST Test_5_NO PROPERTY PASS_REGULAR_EXPRESSION "NO")
