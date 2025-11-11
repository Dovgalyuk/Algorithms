add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_test(NAME TestLab2CPP COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab2CPP PROPERTY PASS_REGULAR_EXPRESSION "ABCD\\+\\*\\+")

add_test(NAME TestLab2CPP1 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab2CPP1 PROPERTY PASS_REGULAR_EXPRESSION "AB\\*C\\+")

add_test(NAME TestLab2CPP2 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab2CPP2 PROPERTY PASS_REGULAR_EXPRESSION  "AB\\+CD-\\*")

add_test(NAME TestLab2CPP3 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab2CPP3 PROPERTY PASS_REGULAR_EXPRESSION "AB\\+C-")

add_test(NAME TestLab2CPP4 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab2CPP4 PROPERTY PASS_REGULAR_EXPRESSION "ABC\\*\\+D\\+")

