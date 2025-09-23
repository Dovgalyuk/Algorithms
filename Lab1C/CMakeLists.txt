add_executable(Lab1C lab1.c)
target_include_directories(Lab1C PUBLIC ../LibraryC ../UtilsC)
target_link_libraries(Lab1C LibraryC)

add_test(NAME TestLab1C1 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input_01.txt)
set_property(TEST TestLab1C1 PROPERTY PASS_REGULAR_EXPRESSION "11")

add_test(NAME TestLab1C2 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input_02.txt)
set_property(TEST TestLab1C2 PROPERTY PASS_REGULAR_EXPRESSION "5 3 2")
