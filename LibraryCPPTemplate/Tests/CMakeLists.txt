add_executable(TestVectorCPPTemplate vector.cpp)
target_include_directories(TestVectorCPPTemplate PUBLIC ..)
add_test(TestVectorCPPTemplate TestVectorCPPTemplate)
set_tests_properties(TestVectorCPPTemplate PROPERTIES TIMEOUT 10)

add_executable(TestGraphCPPTemplate graph.cpp)
target_include_directories(TestGraphCPPTemplate PUBLIC ..)
add_test(TestGraphCPPTemplate TestGraphCPPTemplate)
set_tests_properties(TestGraphCPPTemplate PROPERTIES TIMEOUT 10)

add_executable(TestArrayCPPTemplate array.cpp)
target_include_directories(TestArrayCPPTemplate PUBLIC ..)
add_test(TestArrayCPPTemplate TestArrayCPPTemplate)
set_tests_properties(TestArrayCPPTemplate PROPERTIES TIMEOUT 10)

add_executable(TestHashCPPTemplate hash.cpp)
target_include_directories(TestHashCPPTemplate PUBLIC ..)
add_test(TestHashCPPTemplate TestHashCPPTemplate)
set_tests_properties(TestHashCPPTemplate PROPERTIES TIMEOUT 10)