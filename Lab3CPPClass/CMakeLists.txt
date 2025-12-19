add_executable(lab3cppclass Lab32Struct.cpp)
target_link_libraries(lab3cppclass LibraryCPPClass)
target_include_directories(lab3cppclass PUBLIC . ../LibraryCPPClass)

add_test(NAME Lab3_SimpleMaze
    COMMAND lab3cppclass
        ${CMAKE_CURRENT_SOURCE_DIR}/simple_maze.txt
        simple_output.txt)

add_test(NAME Lab3_MediumMaze
    COMMAND lab3cppclass
        ${CMAKE_CURRENT_SOURCE_DIR}/medium_maze.txt
        medium_output.txt)

add_test(NAME Lab3_NoPathMaze
    COMMAND lab3cppclass
        ${CMAKE_CURRENT_SOURCE_DIR}/nopath_maze.txt
        nopath_output.txt)

set_tests_properties(
    Lab3_SimpleMaze
    Lab3_MediumMaze
    Lab3_NoPathMaze
    PROPERTIES WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}

add_test(NAME Lab3_CheckSimpleOutput
    COMMAND ${CMAKE_COMMAND} -E compare_files
        ${CMAKE_CURRENT_BINARY_DIR}/simple_output.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/expected_simple.txt)

add_test(NAME Lab3_CheckMediumOutput
    COMMAND ${CMAKE_COMMAND} -E compare_files
        ${CMAKE_CURRENT_BINARY_DIR}/medium_output.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/expected_medium.txt)

add_test(NAME Lab3_CheckNoPathOutput
    COMMAND ${CMAKE_COMMAND} -E compare_files
        ${CMAKE_CURRENT_BINARY_DIR}/nopath_output.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/expected_nopath.txt)
