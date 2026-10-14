add_executable(Lab1CPPTask1 task1.cpp)
target_include_directories(Lab1CPPTask1 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPPTask1 LibraryCPP)

add_executable(Lab1CPPTask2 task2.cpp)
target_include_directories(Lab1CPPTask2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPPTask2 LibraryCPP)

# Задание 1
add_test(NAME TestTask1_1 COMMAND Lab1CPPTask1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_input1.txt)
set_property(TEST TestTask1_1 PROPERTY PASS_REGULAR_EXPRESSION "^2[\r\n]*$")

add_test(NAME TestTask1_2 COMMAND Lab1CPPTask1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_input2.txt)
set_property(TEST TestTask1_2 PROPERTY PASS_REGULAR_EXPRESSION "^2 6[\r\n]*$")

add_test(NAME TestTask1_3 COMMAND Lab1CPPTask1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_input3.txt)
set_property(TEST TestTask1_3 PROPERTY PASS_REGULAR_EXPRESSION "^1[\r\n]*$")

add_test(NAME TestTask1_4 COMMAND Lab1CPPTask1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_input4.txt)
set_property(TEST TestTask1_4 PROPERTY PASS_REGULAR_EXPRESSION "^1 4[\r\n]*$")

add_test(NAME TestTask1_5 COMMAND Lab1CPPTask1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_input5.txt)
set_property(TEST TestTask1_5 PROPERTY PASS_REGULAR_EXPRESSION "^1[\r\n]*$")

# Задание 2
add_test(NAME TestTask2_1 COMMAND Lab1CPPTask2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_input1.txt)
set_property(TEST TestTask2_1 PROPERTY PASS_REGULAR_EXPRESSION "^1x3 2x2 3x4 1x1[\r\n]*$")

add_test(NAME TestTask2_2 COMMAND Lab1CPPTask2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_input2.txt)
set_property(TEST TestTask2_2 PROPERTY PASS_REGULAR_EXPRESSION "^1x1 2x1 3x1 4x1 5x1[\r\n]*$")

add_test(NAME TestTask2_3 COMMAND Lab1CPPTask2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_input3.txt)
set_property(TEST TestTask2_3 PROPERTY PASS_REGULAR_EXPRESSION "^7x6[\r\n]*$")

add_test(NAME TestTask2_4 COMMAND Lab1CPPTask2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_input4.txt)
set_property(TEST TestTask2_4 PROPERTY PASS_REGULAR_EXPRESSION "^-1x2 0x3 5x1 -1x2[\r\n]*$")

add_test(NAME TestTask2_5 COMMAND Lab1CPPTask2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_input5.txt)
set_property(TEST TestTask2_5 PROPERTY PASS_REGULAR_EXPRESSION "^[\r\n]*$")
