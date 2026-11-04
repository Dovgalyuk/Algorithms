# add_executable(TestArrayCPPTemplate array.cpp)
# target_include_directories(TestArrayCPPTemplate PUBLIC ..)
# add_test(TestArrayCPPTemplate TestArrayCPPTemplate)

add_executable(TestListCPPTemplate list.cpp)
target_include_directories(TestListCPPTemplate PRIVATE ..)
target_compile_features(TestListCPPTemplate PRIVATE cxx_std_17)
add_test(NAME TestListCPPTemplate COMMAND TestListCPPTemplate)

# add_executable(TestQueueCPPTemplate queue.cpp)
# target_include_directories(TestQueueCPPTemplate PUBLIC ..)
# add_test(TestQueueCPPTemplate TestQueueCPPTemplate)
# set_tests_properties(TestQueueCPPTemplate PROPERTIES TIMEOUT 10)

# add_executable(TestStackCPPTemplate stack.cpp)
# target_include_directories(TestStackCPPTemplate PUBLIC ..)
# add_test(TestStackCPPTemplate TestStackCPPTemplate)

add_executable(TestVectorCPPTemplate vector.cpp)
target_include_directories(TestVectorCPPTemplate PRIVATE ..)
target_compile_features(TestVectorCPPTemplate PRIVATE cxx_std_17)
add_test(NAME TestVectorCPPTemplate COMMAND TestVectorCPPTemplate)
set_tests_properties(TestVectorCPPTemplate PROPERTIES TIMEOUT 10)

add_executable(TestGraphCPPTemplate graph.cpp)
target_include_directories(TestGraphCPPTemplate PRIVATE ..)
target_compile_features(TestGraphCPPTemplate PRIVATE cxx_std_17)
add_test(NAME TestGraphCPPTemplate COMMAND TestGraphCPPTemplate)
set_tests_properties(TestGraphCPPTemplate PROPERTIES TIMEOUT 10)
