add_executable(TestStackCPP main.cpp)
target_include_directories(TestStackCPP PUBLIC ../LibraryCPP)
target_link_libraries(TestStackCPP LibraryCPP)
