add_executable(Lab1C lab1.c)
target_include_directories(Lab1C PUBLIC ../LibraryC)
target_link_libraries(Lab1C LibraryC)

add_test(NAME TestLab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1C PROPERTY PASS_REGULAR_EXPRESSION "0 5 8 8 2 3 5 2 9 4 1 1 7 6 4 7 0 5 8 8
5 6 7 8 9")