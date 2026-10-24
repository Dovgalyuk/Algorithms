add_executable(TestVectorCPP vector.cpp)
add_executable(TestQueueCPP queue.cpp)

target_include_directories(TestVectorCPP PUBLIC ..)
target_include_directories(TestQueueCPP PUBLIC ..)

target_link_libraries(TestVectorCPP LibraryCPP)
target_link_libraries(TestQueueCPP LibraryCPP)

add_test(TestVectorCPP TestVectorCPP)
add_test(TestQueueCPP TestQueueCPP)