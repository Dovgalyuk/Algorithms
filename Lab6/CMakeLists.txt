add_executable(Lab6 lab6.cpp)
add_executable(Comparation cmp.cpp)
include_directories(${CMAKE_SOURCE_DIR}/LibraryCPPTemplate)

add_test(NAME Test1Lab6 COMMAND Lab6 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
add_test(NAME Test2Lab6 COMMAND Lab6 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
add_test(NAME Test3Lab6 COMMAND Lab6 ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)

set_tests_properties(Test1Lab6 PROPERTIES PASS_REGULAR_EXPRESSION "1")
set_tests_properties(Test2Lab6 PROPERTIES PASS_REGULAR_EXPRESSION "12")
set_tests_properties(Test3Lab6 PROPERTIES PASS_REGULAR_EXPRESSION "7")