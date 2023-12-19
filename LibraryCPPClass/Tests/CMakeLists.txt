

add_executable(TestQueueCPPClass queue.cpp)
target_include_directories(TestQueueCPPClass PUBLIC ..)
target_link_libraries(TestQueueCPPClass LibraryCPPClass)
add_test(TestQueueCPPClass TestQueueCPPClass)
set_tests_properties(TestQueueCPPClass PROPERTIES TIMEOUT 10)


add_executable(TestVectorCPPClass vector.cpp)
target_include_directories(TestVectorCPPClass PUBLIC ..)
target_link_libraries(TestVectorCPPClass LibraryCPPClass)
add_test(TestVectorCPPClass TestVectorCPPClass)
set_tests_properties(TestVectorCPPClass PROPERTIES TIMEOUT 10)
