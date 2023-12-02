<<<<<<< Updated upstream
add_executable(TestArrayCPP array.cpp)
target_include_directories(TestArrayCPP PUBLIC ..)
target_link_libraries(TestArrayCPP LibraryCPP)
add_test(TestArrayCPP TestArrayCPP)
=======
add_executable(TestListCPP list.cpp)
target_include_directories(TestListCPP PUBLIC ..)
target_link_libraries(TestListCPP LibraryCPP)
add_test(TestListCPP TestListCPP)

add_executable(TestStackCPP stack.cpp)
target_include_directories(TestStackCPP PUBLIC ..)
target_link_libraries(TestStackCPP LibraryCPP)
add_test(TestStackCPP TestStackCPP)
>>>>>>> Stashed changes
