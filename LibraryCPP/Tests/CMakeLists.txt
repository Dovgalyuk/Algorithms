add_executable(TestListCPP queue.cpp)
target_include_directories(TestListCPP PUBLIC ..)
target_link_libraries(TestListCPP LibraryCPP)
add_test(TestListCPP TestListCPP)

add_executable(TestStackCPP vector.cpp)
target_include_directories(TestStackCPP PUBLIC ..)
target_link_libraries(TestStackCPP LibraryCPP)
add_test(TestStackCPP TestStackCPP)
