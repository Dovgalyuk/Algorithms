add_executable(TestVectorCPP main.cpp)
target_include_directories(TestVectorCPP PUBLIC ../LibraryCPP)
target_link_libraries(TestVectorCPP LibraryCPP)
