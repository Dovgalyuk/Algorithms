add_executable(TestArrayCPPTemplate array.cpp)
target_include_directories(TestArrayCPPTemplate PUBLIC ..)
add_test(TestArrayCPPTemplate TestArrayCPPTemplate)

add_executable(TestListCPPTemplate list.cpp)
target_include_directories(TestListCPPTemplate PUBLIC ..)
add_test(TestListCPPTemplate TestListCPPTemplate)

add_executable(TestQueueCPPTemplate queue.cpp)
target_include_directories(TestQueueCPPTemplate PUBLIC ..)
add_test(TestQueueCPPTemplate TestQueueCPPTemplate)

add_executable(TestStackCPPTemplate stack.cpp)
target_include_directories(TestStackCPPTemplate PUBLIC ..)
add_test(TestStackCPPTemplate TestStackCPPTemplate)

add_executable(TestVectorCPPTemplate vector.cpp)
target_include_directories(TestVectorCPPTemplate PUBLIC ..)
add_test(TestVectorCPPTemplate TestVectorCPPTemplate)
set_tests_properties(TestVectorCPPTemplate PROPERTIES TIMEOUT 10)


add_executable(TestDirectedGraph directed_graph.cpp)
target_include_directories(TestDirectedGraph PUBLIC ..)
add_test(TestDirectedGraph TestDirectedGraph)

add_executable(TestAssociativeArray associative_array.cpp)
target_include_directories(TestAssociativeArray PUBLIC ..)
add_test(TestAssociativeArray TestAssociativeArray)
