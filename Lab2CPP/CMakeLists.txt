add_executable(Lab2CPP 
    lab2.cpp 
    ../LibraryCPP/stack.cpp
    ../LibraryCPP/list.cpp
)

target_include_directories(Lab2CPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../LibraryCPP)

add_test(NAME TestLab2CPP COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab2CPP PROPERTY PASS_REGULAR_EXPRESSION "YES")

add_test(NAME TestLab2CPP1 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab2CPP1 PROPERTY PASS_REGULAR_EXPRESSION "NO")

add_test(NAME TestLab2CPP2 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab2CPP2 PROPERTY PASS_REGULAR_EXPRESSION "NO")

add_test(NAME TestLab2CPP3 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab2CPP3 PROPERTY PASS_REGULAR_EXPRESSION "YES")