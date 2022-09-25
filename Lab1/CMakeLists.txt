add_executable(TaskArrayCPP lab1.cpp)
target_include_directories(TaskArrayCPP PUBLIC ../LibraryCPP)
target_link_libraries(TaskArrayCPP LibraryCPP)