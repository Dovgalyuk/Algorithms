cmake_minimum_required(VERSION 3.10)
project(LibraryCPPTemplate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(GraphLibrary STATIC
    IGraph.h
    AdjacencyMatrixGraph.h
    BFSShortestPaths.h
    vector.h
    test_graph.cpp
)

add_library(LibraryCPPTemplate::GraphLibrary ALIAS GraphLibrary)

add_executable(GraphLibraryTest test_graph.cpp)
target_link_libraries(GraphLibraryTest GraphLibrary)

enable_testing()
add_test(NAME GraphLibraryUnitTest COMMAND GraphLibraryTest)