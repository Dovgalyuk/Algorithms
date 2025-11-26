add_executable(Lab2C lab2.c)
target_include_directories(Lab2C PUBLIC ../LibraryC)
target_link_libraries(Lab2C LibraryC)

add_test(NAME Lab2BasicTest COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST Lab2BasicTest PROPERTY PASS_REGULAR_EXPRESSION "stack:
1
vars:
5
0
0
0")

add_test(NAME Lab2FirstCorrectTest COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST Lab2FirstCorrectTest PROPERTY PASS_REGULAR_EXPRESSION 
"stack:
2
vars:
9
0
0
0")

add_test(NAME Lab2SecondCorrectTest COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST Lab2SecondCorrectTest PROPERTY PASS_REGULAR_EXPRESSION 
"stack:
45
1
vars:
5
0
0
0")

add_test(NAME Lab2ReturnIncorrectTest COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST Lab2ReturnIncorrectTest PROPERTY PASS_REGULAR_EXPRESSION "Error when working with the stack")

add_test(NAME Lab2FirstIncorrectTest COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST Lab2FirstIncorrectTest PROPERTY PASS_REGULAR_EXPRESSION "Error when working with the stack")

add_test(NAME Lab2SecondIncorrectTest COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/input6.txt)
set_property(TEST Lab2SecondIncorrectTest PROPERTY PASS_REGULAR_EXPRESSION "Error when working with the stack")

add_test(NAME Lab2ThirdIncorrectTest COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/input7.txt)
set_property(TEST Lab2ThirdIncorrectTest PROPERTY PASS_REGULAR_EXPRESSION "Error when working with the stack")


