add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PRIVATE ../LibraryCPPTemplate)
target_compile_features(Lab3CPP PRIVATE cxx_std_11)

add_test(
    NAME TestLab3CPP
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
)

set_tests_properties(
    TestLab3CPP
    PROPERTIES
        PASS_REGULAR_EXPRESSION "#[.][.][.]#2[.]3#"
)

function(add_maze_test name regex)
    add_test(
        NAME TestLab3CPP_${name}
        COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/${name}.txt
    )
    set_tests_properties(
        TestLab3CPP_${name}
        PROPERTIES
            PASS_REGULAR_EXPRESSION "${regex}"
    )
endfunction()

add_maze_test(adjacent "#01#")
add_maze_test(snake "#4[.][.][.][.]5[.]#")
add_maze_test(wall "No path")
add_maze_test(detour "#[.][.]#12#")
add_maze_test(enclosed "No path")
add_maze_test(diagonly "#0#[.]#")
add_maze_test(big "[.][.][.][.][.][.][.]2")
add_maze_test(corner "2[.][.]1[.][.][.][.]")