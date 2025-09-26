add_executable(Lab1C lab1.c)
target_include_directories(Lab1C PUBLIC ../LibraryC)
target_link_libraries(Lab1C LibraryC)

add_test(NAME TestLab1C1 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1C1 PROPERTY PASS_REGULAR_EXPRESSION "0 1 2 3 4 5 6 7 8 9 11.*5 3 2")
