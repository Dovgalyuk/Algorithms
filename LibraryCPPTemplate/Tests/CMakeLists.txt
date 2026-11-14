# add_executable(TestArrayCPPTemplate array.cpp)
# target_include_directories(TestArrayCPPTemplate PUBLIC ..)
# add_test(TestArrayCPPTemplate TestArrayCPPTemplate)

add_executable(TestListCPPTemplate list.cpp)
target_include_directories(TestListCPPTemplate PRIVATE ..)
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
add_test(NAME TestVectorCPPTemplate COMMAND TestVectorCPPTemplate)
set_tests_properties(TestVectorCPPTemplate PROPERTIES TIMEOUT 10)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(TestVectorCPPTemplate PRIVATE -Wno-self-assign-overloaded)
endif()

add_executable(TestGraphCPPTemplate graph.cpp)
target_include_directories(TestGraphCPPTemplate PRIVATE ..)
add_test(NAME TestGraphCPPTemplate COMMAND TestGraphCPPTemplate)
