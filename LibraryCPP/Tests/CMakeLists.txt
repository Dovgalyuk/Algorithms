add_executable(TestListCPP list.cpp)
target_link_libraries(TestListCPP PRIVATE LibraryCPP)
add_test(NAME TestListCPP COMMAND TestListCPP)

add_executable(TestQueueCPP queue.cpp)
target_link_libraries(TestQueueCPP PRIVATE LibraryCPP)
add_test(NAME TestQueueCPP COMMAND TestQueueCPP)
set_tests_properties(TestQueueCPP PROPERTIES TIMEOUT 30)

add_executable(TestListExtraCPP list_extra.cpp)
target_link_libraries(TestListExtraCPP PRIVATE LibraryCPP)
add_test(NAME TestListExtraCPP COMMAND TestListExtraCPP)

add_executable(TestQueueExtraCPP queue_extra.cpp)
target_link_libraries(TestQueueExtraCPP PRIVATE LibraryCPP)
add_test(NAME TestQueueExtraCPP COMMAND TestQueueExtraCPP)
set_tests_properties(TestQueueExtraCPP PROPERTIES TIMEOUT 30)

# Keep the maze examples runnable on Windows and Unix without shell redirection.
foreach(case_name IN ITEMS test1 test2 test3 hex_center hex_reverse hex_detour hex_large invalid_empty invalid_duplicate
                           hex_neighbor_0 hex_neighbor_1 hex_neighbor_2 hex_neighbor_3 hex_neighbor_4 hex_neighbor_5)
    add_test(
        NAME Maze_${case_name}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:library_cpp_main>"
            "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/${case_name}.in"
            "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/${case_name}.out"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/RunMazeTest.cmake"
    )
endforeach()
