add_executable(TestListCPP list.cpp)
add_executable(TestStackCPP stack.cpp)

target_include_directories(TestListCPP PUBLIC ..)
target_include_directories(TestStackCPP PUBLIC ..)

target_link_libraries(TestListCPP LibraryCPP)
target_link_libraries(TestStackCPP LibraryCPP)

add_test(TestListCPP TestListCPP)
add_test(TestStackCPP TestStackCPP)