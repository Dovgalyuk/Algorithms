add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PRIVATE ../LibraryCPPTemplate)
target_compile_features(Lab3CPP PRIVATE cxx_std_11)

function(add_maze_test name)
    add_test(
        NAME TestLab3CPP_${name}
        COMMAND ${CMAKE_COMMAND}
            -DEXE=$<TARGET_FILE:Lab3CPP>
            -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${name}.txt
            -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/${name}.out.txt
            -P ${CMAKE_CURRENT_SOURCE_DIR}/compare_output.cmake
    )
endfunction()

add_maze_test(maze1)
add_maze_test(adjacent)
add_maze_test(snake)
add_maze_test(wall)
add_maze_test(detour)
add_maze_test(enclosed)
add_maze_test(diagonly)
add_maze_test(big)
add_maze_test(corner)