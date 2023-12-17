

add_executable(TestListCPP list.cpp)
target_include_directories(TestListCPP PUBLIC ..)
target_link_libraries(TestListCPP LibraryCPP)
add_test(TestListCPP TestListCPP)

add_executable(TestQueueCPP queue.cpp)
target_include_directories(TestQueueCPP PUBLIC ..)
target_link_libraries(TestQueueCPP LibraryCPP)
add_test(TestQueueCPP TestQueueCPP)
set_tests_properties(TestQueueCPP PROPERTIES TIMEOUT 10)


