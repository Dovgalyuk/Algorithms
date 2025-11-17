add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPP LibraryCPPClass)

add_test(NAME StackTest1 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(StackTest1 PROPERTIES PASS_REGULAR_EXPRESSION "BAD PUSH.*2.*STACK.*3.*1")

add_test(NAME StackTest2 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(StackTest2 PROPERTIES PASS_REGULAR_EXPRESSION "10.*BAD POP.*STACK")

add_test(NAME StackTest3 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_tests_properties(StackTest3 PROPERTIES PASS_REGULAR_EXPRESSION "3.*2.*5.*STACK.*1.*4")

add_test(NAME StackTest4 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_tests_properties(StackTest4 PROPERTIES PASS_REGULAR_EXPRESSION "STACK.*1.*2.*3")

add_test(NAME StackTest5 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_tests_properties(StackTest5 PROPERTIES PASS_REGULAR_EXPRESSION "BAD PUSH.*BAD PUSH.*STACK")