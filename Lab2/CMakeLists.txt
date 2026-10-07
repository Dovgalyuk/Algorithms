add_executable(Lab2 lab2.cpp)
target_include_directories(Lab2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab2 LibraryCPP)

add_test(NAME TestLab2 COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab2 PROPERTY PASS_REGULAR_EXPRESSION "POP A[ \t\r\n]+POP B[ \t\r\n]+ADD A, B[ \t\r\n]+PUSH A[ \t\r\n]+PUSH 3[ \t\r\n]+POP A[ \t\r\n]+POP B[ \t\r\n]+MUL A, B[ \t\r\n]+PUSH A")

add_test(NAME TestLab2_1 COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab2_1 PROPERTY PASS_REGULAR_EXPRESSION "MUL A, B[ \t\r\n]+PUSH A[ \t\r\n]+POP A[ \t\r\n]+POP B[ \t\r\n]+ADD A, B[ \t\r\n]+PUSH A")

add_test(NAME TestLab2_2 COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab2_2 PROPERTY PASS_REGULAR_EXPRESSION "ADD A, B[ \t\r\n]+PUSH A[ \t\r\n]+PUSH 3[ \t\r\n]+POP A[ \t\r\n]+POP B[ \t\r\n]+MUL A, B[ \t\r\n]+PUSH A")

add_test(NAME TestLab2_3 COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab2_3 PROPERTY PASS_REGULAR_EXPRESSION "SUB B, A[ \t\r\n]+PUSH B[ \t\r\n]+PUSH 1[ \t\r\n]+PUSH 2[ \t\r\n]+POP A[ \t\r\n]+POP B[ \t\r\n]+ADD A, B[ \t\r\n]+PUSH A[ \t\r\n]+POP A[ \t\r\n]+POP B[ \t\r\n]+SUB B, A[ \t\r\n]+PUSH B")

add_test(NAME TestLab2_4 COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab2_4 PROPERTY PASS_REGULAR_EXPRESSION "ADD A, B[ \t\r\n]+PUSH A[ \t\r\n]+PUSH 8[ \t\r\n]+PUSH 2[ \t\r\n]+POP A[ \t\r\n]+POP B[ \t\r\n]+SUB B, A[ \t\r\n]+PUSH B[ \t\r\n]+POP A[ \t\r\n]+POP B[ \t\r\n]+MUL A, B[ \t\r\n]+PUSH A")

add_test(NAME TestLab2_5 COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST TestLab2_5 PROPERTY PASS_REGULAR_EXPRESSION "MUL A, B[ \t\r\n]+PUSH A[ \t\r\n]+POP A[ \t\r\n]+POP B[ \t\r\n]+SUB B, A[ \t\r\n]+PUSH B")
