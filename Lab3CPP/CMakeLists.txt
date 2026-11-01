add_executable(Maze maze.cpp)
target_include_directories(Maze PRIVATE ../LibraryCPP)
target_link_libraries(Maze PRIVATE LibraryCPP)

add_executable(TestLab3Containers tests/containers.cpp)
target_include_directories(TestLab3Containers PRIVATE ../LibraryCPP)
target_link_libraries(TestLab3Containers PRIVATE LibraryCPP)
add_test(NAME TestLab3Containers COMMAND TestLab3Containers)
set_tests_properties(TestLab3Containers PROPERTIES TIMEOUT 10)

function(add_maze_test name)
    add_test(NAME Maze_${name}
        COMMAND ${CMAKE_COMMAND}
            -DPROGRAM=$<TARGET_FILE:Maze>
            -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/test_data/${name}.txt
            -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/test_data/${name}.expected
            -DEXPECTED_ERROR=${ARGV1}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/RunAndCompare.cmake)
    set_tests_properties(Maze_${name} PROPERTIES TIMEOUT 10)
endfunction()

add_maze_test(example)
add_maze_test(single)
add_maze_test(connected)
add_maze_test(isolated)
add_maze_test(equal_values)
add_maze_test(no_diagonals)
add_maze_test(leftmost_start)
add_maze_test(signed_values)
add_maze_test(integer_limits)
add_maze_test(crlf)
add_maze_test(no_final_newline)
add_maze_test(wide_frontier)
add_maze_test(empty "Maze contains no cells")
add_maze_test(invalid_value "Invalid cell value")
add_maze_test(invalid_alignment "Rows cannot be centered")
