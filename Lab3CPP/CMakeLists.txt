cmake_minimum_required(VERSION 3.14)

project(Lab3)

# Указываем флаги компиляции для macOS
if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
endif()

# Добавляем путь к заголовочным файлам
include_directories(${CMAKE_SOURCE_DIR}/LibraryCPP)

add_executable(Lab3CPP main.cpp)
target_link_libraries(Lab3CPP PRIVATE LibraryCPP)

# Тесты
add_test(NAME Lab3_test1
        COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(Lab3_test1 PROPERTIES PASS_REGULAR_EXPRESSION
        "#########\n#..#...0#\n#.......#\n#...#1###\n#...#2.3#\n#########")

add_test(NAME Lab3_test2_unreachable
        COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input_2.txt)
set_tests_properties(Lab3_test2_unreachable PROPERTIES PASS_REGULAR_EXPRESSION
        "#######\n#Q#..E#\n#######")

add_test(NAME Lab3_test3_one_move
        COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input_3.txt)
set_tests_properties(Lab3_test3_one_move PROPERTIES PASS_REGULAR_EXPRESSION
        "#######\n#0...1#\n#######")

add_test(NAME Lab3_test4_two_moves
        COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input_4.txt)
set_tests_properties(Lab3_test4_two_moves PROPERTIES PASS_REGULAR_EXPRESSION
        "#########\n#0......#\n#......##\n#......##\n#1.....2#\n#########")

add_test(NAME Lab3_test5_no_E
        COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input_5.txt)
set_tests_properties(Lab3_test5_no_E PROPERTIES PASS_REGULAR_EXPRESSION
        "#####\n#Q..#\n#...#\n#####")
