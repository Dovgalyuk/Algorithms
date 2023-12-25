add_executable(TestListCPPTemplate list.cpp)
target_include_directories(TestListCPPTemplate PUBLIC ..)
add_test(TestListCPPTemplate TestListCPPTemplate)

add_executable(TestGraphCPPTemplate graph.cpp)
target_include_directories(TestGraphCPPTemplate PUBLIC ..)
add_test(TestGraphCPPTemplate TestGraphCPPTemplate)
set_tests_properties(TestGraphCPPTemplate PROPERTIES TIMEOUT 10)