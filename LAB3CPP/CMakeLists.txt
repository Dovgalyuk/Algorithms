add_executable(LAB3CPP main.cpp )
target_include_directories(LAB3CPP PUBLIC ../LibraryCPPTemplate)
#target_link_libraries(LAB3CPP LibraryCPPTemplate)

add_test(NAME Test_input COMMAND LAB3CPP ${CMAKE_CURRENT_SOURCE_DIR}/simple_maze.txt)
set_property(TEST Test_input PROPERTY PASS_REGULAR_EXPRESSION "#########.*#..#...0#.*#.......#.*#...#1###.*#...#.23#.*#########")
