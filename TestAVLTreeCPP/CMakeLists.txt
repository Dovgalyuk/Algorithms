add_executable(TestAVLTreeCPP main.cpp)
target_include_directories(TestAVLTreeCPP PUBLIC ../LibraryCPP)
target_link_libraries(TestAVLTreeCPP LibraryCPP)
