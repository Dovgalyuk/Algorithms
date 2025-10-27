add_executable(TestListC list.cpp)
target_include_directories(TestListC PUBLIC ..)
target_link_libraries(TestListC LibraryC)
add_test(TestListC TestListC)


add_executable(TestStackC stack.cpp)
target_include_directories(TestStackC PUBLIC ..)
target_link_libraries(TestStackC LibraryC)
add_test(TestStackC TestStackC)
