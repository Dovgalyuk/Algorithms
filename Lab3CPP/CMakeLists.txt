add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_test(NAME TestLab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab3CPP PROPERTY PASS_REGULAR_EXPRESSION "0\\.######\n..#2....\n.1#.....\n..#.###.\n..#.....\n.....###\n.#####..\n##......")
