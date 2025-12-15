add_executable(lab3cppclass Lab32Struct.cpp)
target_link_libraries(lab3cppclass LibraryCPPClass)
target_include_directories(lab3cppclass PUBLIC 
    .
    ../LibraryCPPClass
)

enable_testing()

add_test(NAME Lab3_SimpleMaze
    COMMAND $<TARGET_FILE:lab3cppclass>
    ${CMAKE_CURRENT_SOURCE_DIR}/simple_maze.txt
    ${CMAKE_CURRENT_BINARY_DIR}/simple_output.txt
)

add_test(NAME Lab3_MediumMaze
    COMMAND $<TARGET_FILE:lab3cppclass>
    ${CMAKE_CURRENT_SOURCE_DIR}/medium_maze.txt
    ${CMAKE_CURRENT_BINARY_DIR}/medium_output.txt
)

add_test(NAME Lab3_NoPathMaze
    COMMAND $<TARGET_FILE:lab3cppclass>
    ${CMAKE_CURRENT_SOURCE_DIR}/no_path_maze.txt
    ${CMAKE_CURRENT_BINARY_DIR}/nopath_output.txt
)

add_test(NAME Lab3_CheckSimpleOutput
    COMMAND bash -c "
        FILE='${CMAKE_CURRENT_BINARY_DIR}/simple_output.txt'
        if [ ! -f \"\$FILE\" ]; then
            echo 'ERROR: File not found: '\$FILE
            exit 1
        fi
        if grep -q 'Path' \"\$FILE\"; then
            echo 'OK: Output contains Path (simple maze)'
            exit 0
        else
            echo 'ERROR: Output does not contain Path'
            exit 1
        fi
    "
)

add_test(NAME Lab3_CheckMediumOutput
    COMMAND bash -c "
        FILE='${CMAKE_CURRENT_BINARY_DIR}/medium_output.txt'
        if [ ! -f \"\$FILE\" ]; then
            echo 'ERROR: File not found: '\$FILE
            exit 1
        fi
        if grep -q 'Path' \"\$FILE\"; then
            echo 'OK: Output contains Path (medium maze)'
            exit 0
        else
            echo 'ERROR: Output does not contain Path'
            exit 1
        fi
    "
)

add_test(NAME Lab3_CheckNoPathOutput
    COMMAND bash -c "
        FILE='${CMAKE_CURRENT_BINARY_DIR}/nopath_output.txt'
        if [ ! -f \"\$FILE\" ]; then
            echo 'ERROR: File not found: '\$FILE
            exit 1
        fi
        if grep -q 'Path' \"\$FILE\"; then
            echo 'OK: Output contains Path (no path maze)'
            exit 0
        else
            echo 'ERROR: Output does not contain Path'
            exit 1
        fi
    "
)

set_tests_properties(
    Lab3_SimpleMaze
    Lab3_MediumMaze
    Lab3_NoPathMaze
    PROPERTIES WILL_FAIL FALSE
)