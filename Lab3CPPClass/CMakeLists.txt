add_executable(lab3cppclass Lab32Struct.cpp)

target_link_libraries(lab3cppclass LibraryCPPClass)

target_include_directories(lab3cppclass PUBLIC 
    .
    ../LibraryCPPClass
)

add_test(NAME Lab3_SimpleMaze COMMAND lab3cppclass simple_maze.txt simple_output.txt)
add_test(NAME Lab3_MediumMaze COMMAND lab3cppclass medium_maze.txt medium_output.txt)
add_test(NAME Lab3_NoPathMaze COMMAND lab3cppclass no_path_maze.txt nopath_output.txt)

set_tests_properties(
    Lab3_SimpleMaze 
    Lab3_MediumMaze 
    Lab3_NoPathMaze 
    PROPERTIES WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Algorithms/Lab3CPPClass
)

set_tests_properties(Lab3_SimpleMaze Lab3_MediumMaze Lab3_NoPathMaze PROPERTIES WILL_FAIL FALSE)
