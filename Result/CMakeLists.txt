add_executable(SolveOne solveone.cpp)
target_include_directories(SolveOne PUBLIC ..)
target_link_libraries(SolveOne LibraryCPP)
add_test(SolveOne SolveOne)