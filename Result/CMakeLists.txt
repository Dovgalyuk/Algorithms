add_executable(SolveOne solveone.cpp)
target_include_directories(SolveOne PUBLIC ../LibraryCPP)
target_link_libraries(SolveOne PUBLIC LibraryCPP)

add_executable(SolveTwo solvetwo.cpp)
target_include_directories(SolveTwo PUBLIC ../LibraryCPPTemplate)

add_executable(SolveThree solvethree.cpp)
target_include_directories(SolveThree PUBLIC ../LibraryCPPTemplate)