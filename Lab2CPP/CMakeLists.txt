cmake_minimum_required(VERSION 3.15)
project(Lab2CPP LANGUAGES CXX)

add_executable(Lab2_Processor processor.cpp)
target_include_directories(Lab2_Processor PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2_Processor LibraryCPPClass)

enable_testing()

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/input1.txt" "PUSH 1\nPOP B\n")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/input2.txt" "PUSH 1\nPUSH 2\nPOP B\nPOP C\nPUSH C\nPOP D\n")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/input3.txt" "PUSH 1\nPUSH 2\nADD B\n")

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/input4.txt" "PUSH 10\nPUSH 4\nSUB A\n")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/input5.txt" "PUSH 3\nPUSH 4\nMUL C\n")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/input6.txt" "POP A\n")

add_test(NAME Test1 COMMAND Lab2_Processor "${CMAKE_CURRENT_BINARY_DIR}/input1.txt")
set_property(TEST Test1 PROPERTY PASS_REGULAR_EXPRESSION "A = 0[\r\n \t]+B = 1[\r\n \t]+C = 0[\r\n \t]+D = 0")

add_test(NAME Test2 COMMAND Lab2_Processor "${CMAKE_CURRENT_BINARY_DIR}/input2.txt")
set_property(TEST Test2 PROPERTY PASS_REGULAR_EXPRESSION "A = 0[\r\n \t]+B = 2[\r\n \t]+C = 1[\r\n \t]+D = 1")

add_test(NAME Test3 COMMAND Lab2_Processor "${CMAKE_CURRENT_BINARY_DIR}/input3.txt")
set_property(TEST Test3 PROPERTY PASS_REGULAR_EXPRESSION "A = 0[\r\n \t]+B = 3[\r\n \t]+C = 0[\r\n \t]+D = 0")

add_test(NAME Test4_SUB COMMAND Lab2_Processor "${CMAKE_CURRENT_BINARY_DIR}/input4.txt")
set_property(TEST Test4_SUB PROPERTY PASS_REGULAR_EXPRESSION "A = 6[\r\n \t]+B = 0[\r\n \t]+C = 0[\r\n \t]+D = 0")

add_test(NAME Test5_MUL COMMAND Lab2_Processor "${CMAKE_CURRENT_BINARY_DIR}/input5.txt")
set_property(TEST Test5_MUL PROPERTY PASS_REGULAR_EXPRESSION "A = 0[\r\n \t]+B = 0[\r\n \t]+C = 12[\r\n \t]+D = 0")

add_test(NAME Test6_Error COMMAND Lab2_Processor "${CMAKE_CURRENT_BINARY_DIR}/input6.txt")
set_property(TEST Test6_Error PROPERTY PASS_REGULAR_EXPRESSION "Error")
