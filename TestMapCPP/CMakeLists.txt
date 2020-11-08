add_executable(TestMapCPP main.cpp)
target_include_directories(TestMapCPP PUBLIC ../LibraryCPP)
target_link_libraries(TestMapCPP LibraryCPP)
