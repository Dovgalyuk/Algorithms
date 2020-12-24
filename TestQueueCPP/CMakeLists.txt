add_executable(TestQueueCPP main.cpp)
target_include_directories(TestQueueCPP PUBLIC ../LibraryCPP)
target_link_libraries(TestQueueCPP LibraryCPP)
