add_executable(TestArrayCPP array.cpp)
target_include_directories(TestArrayCPP PUBLIC ..)
target_link_libraries(TestArrayCPP LibraryCPP)
add_test(TestArrayCPP TestArrayCPP)
