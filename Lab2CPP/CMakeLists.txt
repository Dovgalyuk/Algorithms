add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_test(NAME TestLab2_1 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab2_1 PROPERTY PASS_REGULAR_EXPRESSION "9")

add_test(NAME TestLab2_2 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab2_2 PROPERTY PASS_REGULAR_EXPRESSION "3")

add_test(NAME TestLab2_3 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab2_3 PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME TestLab2_4 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab2_4 PROPERTY PASS_REGULAR_EXPRESSION "14")