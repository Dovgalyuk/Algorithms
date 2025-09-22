add_executable(Lab1CPP main.cpp array.cpp)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set_property(TEST TestLab1CPP PROPERTY PASS_REGULAR_EXPRESSION "Factorial array: 1 1 2 6 24 120 
Most frequent element: 2")