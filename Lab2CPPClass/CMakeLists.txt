add_executable(Lab2CPPClass main.cpp)
target_include_directories(Lab2CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPPClass LibraryCPPClass)

# add some tests
add_test(NAME TestLab2CPPClassMergeExample COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/input_example.txt)
set_tests_properties(TestLab2CPPClassMergeExample PROPERTIES PASS_REGULAR_EXPRESSION "5 12 34 ")

add_test(NAME TestLab2CPPClassMergeEmpty COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/input_empty.txt)
set_tests_properties(TestLab2CPPClassMergeEmpty PROPERTIES PASS_REGULAR_EXPRESSION "")

add_test(NAME TestLab2CPPClassMergeSingle COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/input_single.txt)
set_tests_properties(TestLab2CPPClassMergeSingle PROPERTIES PASS_REGULAR_EXPRESSION "42 ")

add_test(NAME TestLab2CPPClassMergeSorted COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/input_sorted.txt)
set_tests_properties(TestLab2CPPClassMergeSorted PROPERTIES PASS_REGULAR_EXPRESSION "1 2 3 ")

add_test(NAME TestLab2CPPClassMergeReverse COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/input_reverse.txt)
set_tests_properties(TestLab2CPPClassMergeReverse PROPERTIES PASS_REGULAR_EXPRESSION "1 2 3 4 5 ")

add_test(NAME TestLab2CPPClassMergeDups COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/input_dups.txt)
set_tests_properties(TestLab2CPPClassMergeDups PROPERTIES PASS_REGULAR_EXPRESSION "1 2 3 3 ")