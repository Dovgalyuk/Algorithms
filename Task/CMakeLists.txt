add_executable(Task main.cpp)
target_include_directories(Task PUBLIC ../LibraryCPP)
target_link_libraries(Task LibraryCPP)
 
