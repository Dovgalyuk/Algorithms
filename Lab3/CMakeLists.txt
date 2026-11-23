add_executable(Lab3
    src/main.cpp
    src/maze.cpp
)
target_link_libraries(Lab3 PRIVATE Library)

function(add_maze_test test_name)
    add_test(NAME ${test_name}
        COMMAND ${CMAKE_COMMAND}
            -DPROGRAM=$<TARGET_FILE:Lab3>
            -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_name}.txt
            -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_name}.expected
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/check_output.cmake
    )
endfunction()

add_maze_test(test1)
add_maze_test(test2)
add_maze_test(test3)
add_maze_test(test4)