add_executable(TestListCPP list.cpp)
target_link_libraries(TestListCPP PRIVATE LibraryCPP)
add_test(NAME TestListCPP COMMAND TestListCPP)

add_executable(TestQueueCPP queue.cpp)
target_link_libraries(TestQueueCPP PRIVATE LibraryCPP)
add_test(NAME TestQueueCPP COMMAND TestQueueCPP)

# Keep the maze examples runnable on Windows and Unix without shell redirection.
foreach(case_name IN ITEMS test1 test2 test3)
    add_test(
        NAME Maze_${case_name}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:library_cpp_main>"
            "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/${case_name}.in"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/RunMazeTest.cmake"
    )
endforeach()
