add_executable(BFS bfs.cpp)

target_include_directories(BFS PUBLIC ../LibraryCPPTemplate)
target_link_libraries(BFS LibraryCPPTemplate)

add_test(NAME TestBFS COMMAND BFS ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestBFS PROPERTY PASS_REGULAR_EXPRESSION "0\n1\n2\n2")
