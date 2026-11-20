add_executable(Lab3CPPClass main.cpp)
target_link_libraries(Lab3CPPClass LibraryCPPClass)

function(add_maze_test test_name input_file expected_output)
    add_test(
        NAME ${test_name}
        COMMAND Lab3CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/Tests/${input_file}
    )
    set_property(
        TEST ${test_name}
        PROPERTY PASS_REGULAR_EXPRESSION "${expected_output}"
    )
endfunction()

add_maze_test(Lab3_example1 "example1.txt" "^######\r?\n#xxxX#\r?\n#x####\r?\n#xxxY#\r?\n######\r?\n?$")
add_maze_test(Lab3_example2 "example2.txt" "^IMPOSSIBLE\r?\n?$")
add_maze_test(Lab3_adjacent "adjacent.txt" "^####\r?\n#XY#\r?\n####\r?\n?$")
add_maze_test(Lab3_no_border "no_border.txt" "^X\\.#xY\r?\nx##x#\r?\nxxxx#\r?\n?$")
add_maze_test(Lab3_two_routes "two_routes.txt" "^#########\r?\n#XxxxxxY#\r?\n#\\.#####\\.#\r?\n#\\.\\.\\.\\.\\.\\.\\.#\r?\n#########\r?\n?$")
add_maze_test(Lab3_trapped_start "trapped_start.txt" "^IMPOSSIBLE\r?\n?$")
add_maze_test(Lab3_spiral "spiral.txt" "^#########\r?\n#X#xxxxx#\r?\n#x#x###x#\r?\n#xxx#Y#x#\r?\n####\\.xxx#\r?\n#########\r?\n?$")