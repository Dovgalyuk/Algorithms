add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_test(NAME TestLab2CPP1 COMMAND $<TARGET_FILE:Lab2CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab2CPP1 PROPERTY PASS_REGULAR_EXPRESSION  "A = 0
B = 1
C = 0
D = 0
")
add_test(NAME TestLab2CPP2 COMMAND $<TARGET_FILE:Lab2CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab2CPP2 PROPERTY PASS_REGULAR_EXPRESSION  "A = 0
B = 2
C = 1
D = 1
")
add_test(NAME TestLab2CPP3 COMMAND $<TARGET_FILE:Lab2CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab2CPP3 PROPERTY PASS_REGULAR_EXPRESSION  "A = 0
B = 3
C = 0
D = 0
")
