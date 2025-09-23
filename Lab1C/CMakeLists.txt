add_executable(Lab1C lab1.c)
target_include_directories(Lab1C PUBLIC ../LibraryC)
target_link_libraries(Lab1C LibraryC)

add_test(NAME TestLab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1C PROPERTY PASS_REGULAR_EXPRESSION "0 9 8 7 6 5 4 3 2 1.*3 4 5 6 7")

add_test(NAME TestLab1C_1 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab1C_1 PROPERTY PASS_REGULAR_EXPRESSION "6 5 4 3 2 1.*7 3 9 4 8")