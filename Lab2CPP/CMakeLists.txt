add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_test(NAME TestLab2CPP COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab2CPP PROPERTY PASS_REGULAR_EXPRESSION "A = 1.*B = 0.*C = 0.*D = 0")

add_test(NAME TestLab2CPP2 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab2CPP2 PROPERTY PASS_REGULAR_EXPRESSION "BAD.*RET")

add_test(NAME TestLab2CPP3 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab2CPP3 PROPERTY PASS_REGULAR_EXPRESSION "BAD.*POP")

add_test(NAME TestLab2CPP4 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab2CPP4 PROPERTY PASS_REGULAR_EXPRESSION "A = 3.*B = 1.*C = 0.*D = 6")

add_test(NAME TestLab2CPP5 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST TestLab2CPP5 PROPERTY PASS_REGULAR_EXPRESSION "A = 1.*B = 0.*C = 0.*D = 0")
