add_executable(Maze main.cpp)
target_include_directories(Maze PRIVATE ../LibraryCPPClass)
target_link_libraries(Maze LibraryCPPClass)

function(add_maze_test name input expected)
    add_test(NAME ${name} COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:Maze>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/${input}
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/${expected}
        -P ${CMAKE_CURRENT_SOURCE_DIR}/compare.cmake)
endfunction()

add_maze_test(TestMaze input.txt valid.txt)
add_maze_test(TestMazeImpossible input_impossible.txt valid_impossible.txt)
add_maze_test(TestMazeDirect input_direct.txt valid_direct.txt)
add_maze_test(TestMazeLarge input_large.txt valid_large.txt)
