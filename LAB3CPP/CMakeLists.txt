add_executable(LAB3CPP main.cpp )
target_include_directories(LAB3CPP PUBLIC ../LibraryCPPTemplate)
#target_link_libraries(LAB3CPP LibraryCPPTemplate)

add_test(NAME Simple_maze COMMAND LAB3CPP ${CMAKE_CURRENT_SOURCE_DIR}/simple_maze.txt)
set_property(TEST Simple_maze PROPERTY PASS_REGULAR_EXPRESSION "#########.*#..#...0#.*#.......#.*#...#1###.*#...#.23#.*#########")


add_test(NAME Maze_Without_Exit COMMAND LAB3CPP ${CMAKE_CURRENT_SOURCE_DIR}/maze_wiout_exit.txt)
set_property(TEST Maze_Without_Exit PROPERTY PASS_REGULAR_EXPRESSION "Error: Exit not found")


add_test(NAME Maze_close_exit COMMAND LAB3CPP ${CMAKE_CURRENT_SOURCE_DIR}/maze_close_exit.txt)
set_property(TEST Maze_close_exit PROPERTY PASS_REGULAR_EXPRESSION "Error: Exit not found")

add_test(NAME Long_maze COMMAND LAB3CPP ${CMAKE_CURRENT_SOURCE_DIR}/long_maze.txt)
set_property(TEST Long_maze PROPERTY PASS_REGULAR_EXPRESSION "###############.*#76.5....#....#.*###5###.#.#.###.*#...#...#.#.#.#.*#4#####.#.#.#.#.*#.#.....#.#.#.#.*#.#.###.#.#.#.#.*#.#.#...#.#.#.#.*#.#.#.###.#.#.#.*#.#.#.#...#.#.#.*#3#.#.#.#.###.#.*#...#.#.#.....#.*###2###.#####.#.*#0111.........#.*###############")

add_test(NAME Maze_is_not_rectangle COMMAND LAB3CPP ${CMAKE_CURRENT_SOURCE_DIR}/error_maze.txt)
set_property(TEST Maze_is_not_rectangle PROPERTY PASS_REGULAR_EXPRESSION "Error")

