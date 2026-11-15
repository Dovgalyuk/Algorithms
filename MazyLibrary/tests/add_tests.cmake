# Include after add_executable(maze_path ...).
# If your executable target has another name, replace maze_path below.

file(GLOB maze_inputs CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.in")

foreach(input IN LISTS maze_inputs)
    get_filename_component(test_name "${input}" NAME_WE)
    add_test(NAME advanced_${test_name}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:maze_path>"
            "-DINPUT=${input}"
            "-DEXPECTED=${CMAKE_CURRENT_LIST_DIR}/${test_name}.out"
            -P "${CMAKE_CURRENT_LIST_DIR}/check.cmake"
    )
endforeach()

# Verify argv[1] file mode, not only stdin.
foreach(test_name IN ITEMS maze_path maze_windows_crlf maze_snake_81x101)
    add_test(NAME advanced_file_${test_name}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:maze_path>"
            "-DINPUT=${CMAKE_CURRENT_LIST_DIR}/${test_name}.in"
            "-DEXPECTED=${CMAKE_CURRENT_LIST_DIR}/${test_name}.out"
            "-DMODE=arg"
            -P "${CMAKE_CURRENT_LIST_DIR}/check.cmake"
    )
endforeach()
