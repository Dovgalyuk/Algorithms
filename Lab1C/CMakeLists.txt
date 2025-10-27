add_executable(Lab1C lab1.c)
target_include_directories(Lab1C PUBLIC ../LibraryC ../UtilsC)
target_link_libraries(Lab1C LibraryC)

# Test with default input.txt
add_test(NAME TestLab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1C PROPERTY PASS_REGULAR_EXPRESSION "0 5 8 8 2 3 5 2 9.*1")

# Test 1
add_test(NAME TestLab1C1 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test_input_01.txt)
set_property(TEST TestLab1C1 PROPERTY PASS_REGULAR_EXPRESSION "\n\n")

# Test 2
add_test(NAME TestLab1C2 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test_input_02.txt)
set_property(TEST TestLab1C2 PROPERTY PASS_REGULAR_EXPRESSION "0.*5 7 11 13")

# Test 3
add_test(NAME TestLab1C3 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test_input_03.txt)
set_property(TEST TestLab1C3 PROPERTY PASS_REGULAR_EXPRESSION "0 5 8 8 2 3 5 2 9.*5")