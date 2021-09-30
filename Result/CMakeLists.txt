add_executable(SolveOne solveone.cpp)
target_include_directories(SolveOne PUBLIC ../LibraryCPP)

target_link_libraries(SolveOne PUBLIC LibraryCPP)