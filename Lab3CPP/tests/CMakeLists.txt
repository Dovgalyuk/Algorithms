foreach(case_name IN ITEMS test1 test2 test3 hex_center hex_reverse hex_detour hex_large hex_branches
                           hex_branches_large hex_branches_detour equal_rows equal_rows_reverse
                           invalid_empty invalid_duplicate hex_neighbor_0 hex_neighbor_1 hex_neighbor_2
                           hex_neighbor_3 hex_neighbor_4 hex_neighbor_5)
    add_test(
        NAME Maze_${case_name}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:maze_solver>"
            "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/${case_name}.in"
            "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/${case_name}.out"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/RunMazeTest.cmake"
    )
endforeach()
