cmake_minimum_required(VERSION 3.10)

add_executable(Lab1C_PR main.cpp)

target_include_directories(Lab1C_PR PUBLIC ../LibraryCPP)

target_link_libraries(Lab1C_PR LibraryCPP)

enable_testing()

add_test(NAME TestLab1C_PR COMMAND Lab1C_PR ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set_property(TEST TestLab1C_PR PROPERTY PASS_REGULAR_EXPRESSION "Task 4: Number of elements > sum \\(.*\\): 0;Task 5: Max sum: 114")