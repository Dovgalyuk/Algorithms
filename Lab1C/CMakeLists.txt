add_executable(Lab1C Lab1.cpp)
target_include_directories(Lab1C PUBLIC ../LibraryCPP)
target_link_libraries(Lab1C LibraryCPP)

# Тест 1: Fibonachi
add_test(NAME TestFibonachi COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestFibonachi PROPERTY PASS_REGULAR_EXPRESSION "0 1 1 2 3 5 8 13 21 34")

# Тест 2: Compressed array
add_test(NAME TestCompressed COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestCompressed PROPERTY PASS_REGULAR_EXPRESSION "20 3 25 0 0 0 0 0")