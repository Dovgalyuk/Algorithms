add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_test(NAME Test1 COMMAND Lab3CPP "input1.txt")
add_test(NAME Test2 COMMAND Lab3CPP "input2.txt")
add_test(NAME Test3 COMMAND Lab3CPP "input3.txt")

set_tests_properties(Test1 PROPERTIES PASS_REGULAR_EXPRESSION "4")
set_tests_properties(Test2 PROPERTIES PASS_REGULAR_EXPRESSION "4")
set_tests_properties(Test3 PROPERTIES PASS_REGULAR_EXPRESSION "5")
