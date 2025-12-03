

add_executable(TestGraphCPPTemplate graph.cpp)
target_include_directories(TestGraphCPPTemplate PUBLIC ..)
target_compile_definitions(TestGraphCPPTemplate PRIVATE TEST_GRAPH_STANDALONE)
add_test(NAME TestGraphCPPTemplate COMMAND TestGraphCPPTemplate)
set_tests_properties(TestGraphCPPTemplate PROPERTIES TIMEOUT 10)

add_executable(TestListCPPTemplate list.cpp)
target_include_directories(TestListCPPTemplate PUBLIC ..)
add_test(NAME TestListCPPTemplate COMMAND TestListCPPTemplate)
set_tests_properties(TestListCPPTemplate PROPERTIES TIMEOUT 10)

# add_executable(TestArrayCPPTemplate array.cpp)
# target_include_directories(TestArrayCPPTemplate PUBLIC ..)
# add_test(NAME TestArrayCPPTemplate COMMAND TestArrayCPPTemplate)

# add_executable(TestQueueCPPTemplate queue.cpp)
# target_include_directories(TestQueueCPPTemplate PUBLIC ..)
# add_test(NAME TestQueueCPPTemplate COMMAND TestQueueCPPTemplate)
# set_tests_properties(TestQueueCPPTemplate PROPERTIES TIMEOUT 10)

# add_executable(TestStackCPPTemplate stack.cpp)
# target_include_directories(TestStackCPPTemplate PUBLIC ..)
# add_test(NAME TestStackCPPTemplate COMMAND TestStackCPPTemplate)

# add_executable(TestVectorCPPTemplate vector.cpp)
# target_include_directories(TestVectorCPPTemplate PUBLIC ..)
# add_test(NAME TestVectorCPPTemplate COMMAND TestVectorCPPTemplate)
# set_tests_properties(TestVectorCPPTemplate PROPERTIES TIMEOUT 10)