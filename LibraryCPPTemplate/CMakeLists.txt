
add_executable(TestListCPPTemplate list.cpp)
target_include_directories(TestListCPPTemplate PUBLIC ..)
add_test(TestListCPPTemplate TestListCPPTemplate)


add_executable(TestgraphCPPTemplate graph.cpp)
target_include_directories(TestgraphCPPTemplate PUBLIC ..)
add_test(TestgraphCPPTemplate TestgraphCPPTemplate)
