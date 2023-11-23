add_executable(TestArrayCPPTemplate array.cpp)
target_include_directories(TestArrayCPPTemplate PUBLIC ..)
add_test(TestArrayCPPTemplate TestArrayCPPTemplate)

add_executable(TestAvlCPPTemplate avl.cpp)
target_include_directories(TestAvlCPPTemplate PUBLIC ..)
add_test(TestAvlCPPTemplate TestAvlCPPTemplate)

