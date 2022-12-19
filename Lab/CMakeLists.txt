add_executable(TaskArrayCPP array.cpp )
target_include_directories(TaskArrayCPP PUBLIC ../LibraryCPP)
target_link_libraries(TaskArrayCPP LibraryCPP)