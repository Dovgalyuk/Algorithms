add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_test(NAME Test1Lab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
add_test(NAME Test2Lab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
add_test(NAME Test3Lab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)

set_tests_properties(Test1Lab3CPP PROPERTIES PASS_REGULAR_EXPRESSION "4")
set_tests_properties(Test2Lab3CPP PROPERTIES PASS_REGULAR_EXPRESSION "4")
set_tests_properties(Test3Lab3CPP PROPERTIES PASS_REGULAR_EXPRESSION "5")
