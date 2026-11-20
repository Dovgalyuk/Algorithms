add_executable(Maze maze.cpp)
target_include_directories(Maze PRIVATE ../LibraryCPP)
target_link_libraries(Maze LibraryCPP)

function(add_maze_test name input expected)
    add_test(NAME ${name} COMMAND ${CMAKE_COMMAND}
        "-DPROGRAM=$<TARGET_FILE:Maze>"
        "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/${input}"
        "-DEXPECTED=${expected}"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/check_output.cmake")
endfunction()

add_maze_test(TestMazeExample example.txt 4)
add_maze_test(TestMazeUnreachable unreachable.txt -1)
add_maze_test(TestMazeBoundary boundary.txt 0)
add_maze_test(TestMazeTie tie.txt 2)
add_maze_test(TestMazeDetour detour.txt 7)
