add_executable(Lab3Cpp lab3.cpp)
target_include_directories(Lab3Cpp PUBLIC ../LibraryCPP)
target_link_libraries(Lab3Cpp LibraryCPP)

add_test(NAME TestLab3Cpp_1 COMMAND Lab3Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab3Cpp_1 PROPERTY PASS_REGULAR_EXPRESSION "######.*#xxxX#.*#x####.*#xxxY#.*######")

add_test(NAME TestLab3Cpp_2 COMMAND Lab3Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab3Cpp_2 PROPERTY PASS_REGULAR_EXPRESSION "IMPOSSIBLE")

add_test(NAME TestLab3Cpp_3 COMMAND Lab3Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab3Cpp_3 PROPERTY PASS_REGULAR_EXPRESSION "########.*#\\.\\.\\.\\.\\.\\.#.*#\\.####\\.#.*#\\.#\\.\\.#\\.#.*#X#\\.\\.#Y#.*#x####x#.*#xxxxxx#.*########")

add_test(NAME TestLab3Cpp_4 COMMAND Lab3Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab3Cpp_4 PROPERTY PASS_REGULAR_EXPRESSION "##########.*#........#.*#.######.#.*#.#....#.#.*#.#.##.#.#.*#X#....#Y#.*#x######x#.*#xxxxxxxx#.*##########")

add_test(NAME TestLab3Cpp_5 COMMAND Lab3Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST TestLab3Cpp_5 PROPERTY PASS_REGULAR_EXPRESSION "############.*#xxxxxxxxxx#.*#x########x#.*#x#......#x#.*#x#.####.#x#.*#X#......#Y#.*#.#.####.#.#.*#.#......#.#.*#.########.#.*#..........#.*############")
