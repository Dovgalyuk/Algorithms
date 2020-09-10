add_executable(TestListCPP main.cpp)
target_include_directories(TestListCPP PUBLIC ../LibraryCPP)
target_link_libraries(TestListCPP LibraryCPP)
