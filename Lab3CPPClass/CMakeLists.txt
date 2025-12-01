cmake_minimum_required(VERSION 3.10)
project(lab3cppclass)

add_executable(lab3cppclass Lab32Struct.cpp list.cpp queue.cpp)
target_include_directories(lab3cppclass PUBLIC .)

add_test(NAME Lab3_SimpleMaze COMMAND lab3cppclass simple_maze.txt simple_output.txt)
add_test(NAME Lab3_MediumMaze COMMAND lab3cppclass medium_maze.txt medium_output.txt)
add_test(NAME Lab3_NoPathMaze COMMAND lab3cppclass no_path_maze.txt nopath_output.txt)

set_tests_properties(Lab3_SimpleMaze Lab3_MediumMaze PROPERTIES WILL_FAIL FALSE)

enable_testing()
