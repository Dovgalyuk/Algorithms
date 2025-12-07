add_executable(Lab4CPP main.cpp)
target_include_directories (Lab4CPP PUBLIC ../LibraryCPPTemplate)

add_test(NAME Test_1 COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1_4.txt)
set_tests_properties(Test_1 PROPERTIES PASS_REGULAR_EXPRESSION "11.*A B D E")
add_test(NAME Test_2 COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2_4.txt)
set_tests_properties(Test_2 PROPERTIES PASS_REGULAR_EXPRESSION "No path")