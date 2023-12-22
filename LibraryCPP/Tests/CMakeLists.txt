add_executable(TestArrayCPP array.cpp)
target_include_directories(TestArrayCPP PUBLIC ..)
target_link_libraries(TestArrayCPP LibraryCPP)
add_test(TestArrayCPP TestArrayCPP)

add_executable(TestStackCPPClass stack.cpp)
target_include_directories(TestStackCPPClass PUBLIC ..)
target_link_libraries(TestStackCPPClass LibraryCPPClass)
add_test(TestStackCPPClass TestStackCPPClass)

add_executable(TestListCPPClass list.cpp)
target_include_directories(TestListCPPClass PUBLIC ..)
target_link_libraries(TestListCPPClass LibraryCPPClass)
add_test(TestListCPPClass TestListCPPClass)
