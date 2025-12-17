set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab6 main.cpp Benchmark.cpp DPSolver.cpp ExhaustiveSolver.cpp MatrixChain.cpp utility.cpp)

target_include_directories(Lab6 PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab6 LibraryCPPTemplate)

add_subdirectory("Test")