add_executable(Maze maze.cpp)

target_link_libraries(Maze PRIVATE LibraryCPP)

function(add_maze_test name input_file expected)
    add_test(
        NAME ${name}
        COMMAND powershell -NoProfile -Command
            "$actual = & '$<TARGET_FILE:Maze>' '${CMAKE_CURRENT_SOURCE_DIR}/Tests/${input_file}'; if ($LASTEXITCODE -ne 0) { exit 1 }; if (($actual -join ' ').Trim() -ne '${expected}') { Write-Error 'Expected ${expected}, got: ' + ($actual -join ' '); exit 1 }"
    )
endfunction()

function(add_maze_error_test name input_file)
    add_test(
        NAME ${name}
        COMMAND powershell -NoProfile -Command
            "$null = & '$<TARGET_FILE:Maze>' '${CMAKE_CURRENT_SOURCE_DIR}/Tests/${input_file}' 2>&1; $code = $LASTEXITCODE; if ($code -ne 1) { Write-Error ('Expected exit code 1, got ' + $code); exit 1 }"
    )
endfunction()

add_maze_test(sample GitMaze.txt 4)
add_maze_test(closest_exit maze2.txt 2)
add_maze_test(unreachable maze3.txt -1)
add_maze_test(adjacent_exit maze4.txt 1)
add_maze_test(boundary maze5.txt 1)
add_maze_test(left_exit maze6.txt 0)
add_maze_test(right_exit maze7.txt 5)
add_maze_test(top_exit maze8.txt 2)
add_maze_test(bottom_exit maze9.txt 7)
add_maze_test(multiple_exits maze10.txt 0)
add_maze_test(long_corridor maze11.txt 8)
add_maze_test(dead_end maze12.txt 4)
add_maze_test(turns maze14.txt 2)
add_maze_test(open_area maze15.txt 9)
add_maze_error_test(ErrorNoStart error1.txt)
add_maze_error_test(ErrorMultipleStarts error2.txt)
add_maze_error_test(ErrorInvalidCharacter error3.txt)
add_maze_error_test(ErrorNonRectangular error4.txt)
add_maze_error_test(ErrorEmptyFile error5.txt)
add_maze_error_test(ErrorEmptyLine error6.txt)
add_maze_error_test(ErrorOnlyWalls error7.txt)
add_maze_error_test(ErrorNoExits error8.txt)
add_maze_error_test(ErrorMissingFile missing.txt)