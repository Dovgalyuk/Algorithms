add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_test(NAME TestLab2CPP COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab2CPP PROPERTY PASS_REGULAR_EXPRESSION "1\r?\n2\r?\n3\r?\n6\r?\n")

add_test(NAME TestLab2CPP_1 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab2CPP_1 PROPERTY PASS_REGULAR_EXPRESSION "3\r?\n2\r?\n1\r?\n")

add_test(NAME TestLab2CPP_2 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab2CPP_2 PROPERTY PASS_REGULAR_EXPRESSION "4\r?\n1\r?\n1\r?\n")

add_test(NAME TestLab2CPP_3 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab2CPP_3 PROPERTY PASS_REGULAR_EXPRESSION "13\r?\n")

add_test(NAME TestLab2CPP_4 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab2CPP_4 PROPERTY PASS_REGULAR_EXPRESSION "0\r?\n1\r?\n")