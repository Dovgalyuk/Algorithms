add_executable(Lab1C lab2.cpp)
target_include_directories(Lab1C PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1C LibraryCPPClass)

add_test(NAME TestLab2CPP COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab2CPP PROPERTY PASS_REGULAR_EXPRESSION "BAD RET")

add_test(NAME TestLab2CPP2 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab2CPP2 PROPERTY PASS_REGULAR_EXPRESSION "A = 1\nB = 0\nC = 0\nD = 0")
