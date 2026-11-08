add_executable(maze_solver main.cpp)
target_include_directories(maze_solver PRIVATE ../LibraryCPP)
target_link_libraries(maze_solver PRIVATE LibraryCPP)
add_subdirectory(tests)