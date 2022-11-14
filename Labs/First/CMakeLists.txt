add_executable(First lab1.cpp)
target_include_directories(First PUBLIC ../LibraryCPP)
target_link_libraries(First LibraryCPP)
