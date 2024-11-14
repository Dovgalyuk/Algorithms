add_executable(Lab4CPP lab4.cpp)
include_directories(${CMAKE_SOURCE_DIR}/LibraryCPPTemplate)

add_test(NAME Test1Lab4CPP COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
add_test(NAME Test2Lab4CPP COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
add_test(NAME Test3Lab4CPP COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)

set_tests_properties(Test1Lab4CPP PROPERTIES PASS_REGULAR_EXPRESSION "1")
set_tests_properties(Test2Lab4CPP PROPERTIES PASS_REGULAR_EXPRESSION "12")
set_tests_properties(Test3Lab4CPP PROPERTIES PASS_REGULAR_EXPRESSION "7")