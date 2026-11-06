cmake_minimum_required(VERSION 3.15)
project(Lab3CPP LANGUAGES CXX)

add_executable(Lab3_Maze maze.cpp)
target_include_directories(Lab3_Maze PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab3_Maze LibraryCPPClass)

enable_testing()

add_test(NAME MazeTest1 COMMAND Lab3_Maze "${CMAKE_CURRENT_SOURCE_DIR}/input1.txt")
set_property(TEST MazeTest1 PROPERTY PASS_REGULAR_EXPRESSION "4")

add_test(NAME MazeTest2 COMMAND Lab3_Maze "${CMAKE_CURRENT_SOURCE_DIR}/input2.txt")
set_property(TEST MazeTest2 PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME MazeTest3 COMMAND Lab3_Maze "${CMAKE_CURRENT_SOURCE_DIR}/input3.txt")
set_property(TEST MazeTest3 PROPERTY PASS_REGULAR_EXPRESSION "No exit found")