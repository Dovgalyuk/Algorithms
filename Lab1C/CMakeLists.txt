add_executable(Lab1C lab1.c)
target_include_directories(Lab1C PUBLIC ../LibraryC)
target_link_libraries(Lab1C LibraryC)

add_test(NAME TestLab1C_Task1 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1C_Task1 PROPERTY PASS_REGULAR_EXPRESSION "36")

add_test(NAME TestLab1C_Task2 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1C_Task2 PROPERTY PASS_REGULAR_EXPRESSION "1 4 0 0")
