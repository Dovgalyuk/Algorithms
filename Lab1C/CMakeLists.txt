cmake_minimum_required(VERSION 3.10)
project(Lab1C C)

set(CMAKE_C_STANDARD 11)

add_library(LibraryC STATIC ../LibraryC/array.cpp)
target_include_directories(LibraryC PUBLIC ../LibraryC)

add_executable(Lab1C lab1.cpp)
target_include_directories(Lab1C PUBLIC ../LibraryC)
target_link_libraries(Lab1C LibraryC)



enable_testing()

add_test(NAME TestLab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab1C PROPERTIES PASS_REGULAR_EXPRESSION "Task1:.*Task2:.*")

add_test(NAME TestLab1C_2 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(TestLab1C_2 PROPERTIES PASS_REGULAR_EXPRESSION "Task1:.*Task2:.*")