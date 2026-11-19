add_executable(Lab3 main.cpp)
target_include_directories(Lab3 PRIVATE ../LibraryCPPClass)
target_link_libraries(Lab3 PRIVATE LibraryCPPClass)

function(add_maze_test name input expected)
    add_test(NAME ${name} COMMAND "${CMAKE_COMMAND}"
        "-DPROGRAM=$<TARGET_FILE:Lab3>"
        "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/${input}"
        "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/${expected}"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/test.cmake")
endfunction()

add_maze_test(TestLab3 input.txt expected.txt)
add_maze_test(TestLab3_adjacent tests/adjacent.in tests/adjacent.out.txt)
add_maze_test(TestLab3_horizontal_left tests/horizontal_left.in tests/horizontal_left.out.txt)
add_maze_test(TestLab3_vertical_up tests/vertical_up.in tests/vertical_up.out.txt)
add_maze_test(TestLab3_diagonal tests/diagonal.in tests/diagonal.out.txt)
add_maze_test(TestLab3_blocked tests/blocked.in tests/blocked.out.txt)
add_maze_test(TestLab3_long_zigzag tests/long_zigzag.in tests/long_zigzag.out.txt)
