add_executable(Maze maze.cpp)
target_include_directories(Maze PRIVATE ../LibraryCPP)
target_link_libraries(Maze PRIVATE LibraryCPP)

add_test(
    NAME TestMazeExample
    COMMAND Maze "${CMAKE_CURRENT_SOURCE_DIR}/tests/maze_input.txt"
)

set_tests_properties(TestMazeExample PROPERTIES
    PASS_REGULAR_EXPRESSION "^ / \\\\ / \\\\ / \\\\[\r\n]+[|] S [|] # [|]   [|][\r\n]+ \\\\ / \\\\ / \\\\ / \\\\[\r\n]+  [|] x [|] # [|] # [|][\r\n]+   \\\\ / \\\\ / \\\\ / \\\\[\r\n]+    [|] x [|] x [|] E [|][\r\n]+     \\\\ / \\\\ / \\\\ /[\r\n]*$"
    TIMEOUT 10
)

add_test(
    NAME TestMazeAdjacent
    COMMAND Maze "${CMAKE_CURRENT_SOURCE_DIR}/tests/maze_adjacent.txt"
)

set_tests_properties(TestMazeAdjacent PROPERTIES
    PASS_REGULAR_EXPRESSION "^ / \\\\ / \\\\[\r\n]+[|] S [|] E [|][\r\n]+ \\\\ / \\\\ /[\r\n]*$"
    TIMEOUT 10
)

add_test(
    NAME TestMazeSingleColumn
    COMMAND Maze "${CMAKE_CURRENT_SOURCE_DIR}/tests/maze_column.txt"
)

set_tests_properties(TestMazeSingleColumn PROPERTIES
    PASS_REGULAR_EXPRESSION "^ / \\\\[\r\n]+[|] E [|][\r\n]+ \\\\ / \\\\[\r\n]+  [|] x [|][\r\n]+   \\\\ / \\\\[\r\n]+    [|] S [|][\r\n]+     \\\\ /[\r\n]*$"
    TIMEOUT 10
)

add_test(
    NAME TestMazeDiagonalDown
    COMMAND Maze "${CMAKE_CURRENT_SOURCE_DIR}/tests/maze_diagonal_down.txt"
)

set_tests_properties(TestMazeDiagonalDown PROPERTIES
    PASS_REGULAR_EXPRESSION "^ / \\\\ / \\\\ / \\\\[\r\n]+[|] # [|] # [|] S [|][\r\n]+ \\\\ / \\\\ / \\\\ / \\\\[\r\n]+  [|] # [|] x [|] # [|][\r\n]+   \\\\ / \\\\ / \\\\ / \\\\[\r\n]+    [|] E [|] # [|] # [|][\r\n]+     \\\\ / \\\\ / \\\\ /[\r\n]*$"
    TIMEOUT 10
)

add_test(
    NAME TestMazeDiagonalUp
    COMMAND Maze "${CMAKE_CURRENT_SOURCE_DIR}/tests/maze_diagonal_up.txt"
)

set_tests_properties(TestMazeDiagonalUp PROPERTIES
    PASS_REGULAR_EXPRESSION "^ / \\\\ / \\\\ / \\\\[\r\n]+[|] # [|] # [|] E [|][\r\n]+ \\\\ / \\\\ / \\\\ / \\\\[\r\n]+  [|] # [|] x [|] # [|][\r\n]+   \\\\ / \\\\ / \\\\ / \\\\[\r\n]+    [|] S [|] # [|] # [|][\r\n]+     \\\\ / \\\\ / \\\\ /[\r\n]*$"
    TIMEOUT 10
)

add_test(
    NAME TestMazeShortest
    COMMAND Maze "${CMAKE_CURRENT_SOURCE_DIR}/tests/maze_shortest.txt"
)

set_tests_properties(TestMazeShortest PROPERTIES
    PASS_REGULAR_EXPRESSION "^ / \\\\ / \\\\ / \\\\ / \\\\[\r\n]+[|] S [|] x [|] x [|] E [|][\r\n]+ \\\\ / \\\\ / \\\\ / \\\\ / \\\\[\r\n]+  [|]   [|]   [|]   [|]   [|][\r\n]+   \\\\ / \\\\ / \\\\ / \\\\ /[\r\n]*$"
    TIMEOUT 10
)

add_test(
    NAME TestMazeNoPath
    COMMAND Maze "${CMAKE_CURRENT_SOURCE_DIR}/tests/maze_no_path.txt"
)

set_tests_properties(TestMazeNoPath PROPERTIES
    PASS_REGULAR_EXPRESSION "^No path found[\r\n]*$"
    TIMEOUT 10
)

add_test(
    NAME TestMazeForbiddenDiagonal
    COMMAND Maze "${CMAKE_CURRENT_SOURCE_DIR}/tests/maze_forbidden_diagonal.txt"
)

set_tests_properties(TestMazeForbiddenDiagonal PROPERTIES
    PASS_REGULAR_EXPRESSION "^No path found[\r\n]*$"
    TIMEOUT 10
)
