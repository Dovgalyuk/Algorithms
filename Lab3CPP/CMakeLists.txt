cmake_minimum_required(VERSION 3.20)

project(Lab3CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab3CPP main.cpp)

target_link_libraries(Lab3CPP PRIVATE LibraryCPP)

enable_testing()

add_test(
        NAME maze_test1
        COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_maze1.txt
)
set_tests_properties(maze_test1 PROPERTIES PASS_REGULAR_EXPRESSION "^ /[^x]*x[^x]*x[^x]*x[^x]*$")

add_test(
        NAME maze_test2
        COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_maze2.txt
)
set_tests_properties(maze_test2 PROPERTIES PASS_REGULAR_EXPRESSION "^NO PATH")

add_test(
        NAME maze_test3
        COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_maze3.txt
)
set_tests_properties(maze_test3 PROPERTIES PASS_REGULAR_EXPRESSION "^ /[^x]*$")

add_test(
        NAME maze_test4
        COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_maze4.txt
)
set_tests_properties(maze_test4 PROPERTIES PASS_REGULAR_EXPRESSION "^ /[^x]*x[^x]*$")

add_test(
        NAME maze_test5
        COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_maze5.txt
)
set_tests_properties(maze_test5 PROPERTIES PASS_REGULAR_EXPRESSION "^ /[^x]*x[^x]*x[^x]*x[^x]*$")

add_test(
        NAME maze_test6
        COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_maze6.txt
)
set_tests_properties(maze_test6 PROPERTIES PASS_REGULAR_EXPRESSION "^ /[^x]*x[^x]*x[^x]*x[^x]*x[^x]*$")
