add_executable(TestArrayCPP main.cpp)
target_include_directories(TestArrayCPP PUBLIC ../LibraryCPP)
target_link_libraries(TestArrayCPP LibraryCPP)

add_test(TestArrayCPP TestArrayCPP)
