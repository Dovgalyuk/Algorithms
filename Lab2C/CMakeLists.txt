add_executable(Lab2C lab2.c interpreter.c)
target_include_directories(Lab2C PUBLIC ../LibraryC)
target_link_libraries(Lab2C LibraryC)

# Test 1: Basic push and reverse with output
add_test(NAME TestLab2C_BasicPush 
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_01_plus_script.txt 
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_01_plus_input.txt)
set_property(TEST TestLab2C_BasicPush PROPERTY PASS_REGULAR_EXPRESSION "^d.*l.*r.*o.*W.*o.*l.*l.*e.*H")

# Test 2: Push, reverse, and output tilde
add_test(NAME TestLab2C_Reverse 
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_02_reverse_script.txt 
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_02_reverse_input.txt)
set_property(TEST TestLab2C_Reverse PROPERTY PASS_REGULAR_EXPRESSION "A.*B.*C")

# Test 3: Concatenation test
add_test(NAME TestLab2C_Concat 
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_03_concat_script.txt 
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_03_concat_input.txt)
set_property(TEST TestLab2C_Concat PROPERTY PASS_REGULAR_EXPRESSION "olleH")

# Test 4: Tilde get and clear
add_test(NAME TestLab2C_TildeClear 
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_04_tilde_script.txt 
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_04_tilde_input.txt)
set_property(TEST TestLab2C_TildeClear PROPERTY PASS_REGULAR_EXPRESSION "X.*X")

# Test 5: Remove bottom element
add_test(NAME TestLab2C_RemoveBottom 
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_05_remove_bottom_script.txt 
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_05_remove_bottom_input.txt)
set_property(TEST TestLab2C_RemoveBottom PROPERTY PASS_REGULAR_EXPRESSION "C.*B")

# Test 6: Cat program - read input and echo it
add_test(NAME TestLab2C_Cat 
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_06_cat_script.txt 
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_06_cat_input.txt)
set_property(TEST TestLab2C_Cat PROPERTY PASS_REGULAR_EXPRESSION "HelloWorld")

# Test 7: Hello World - simple string output
add_test(NAME TestLab2C_HelloWorld 
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_07_hello_world_script.txt 
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_07_hello_world_input.txt)
set_property(TEST TestLab2C_HelloWorld PROPERTY PASS_REGULAR_EXPRESSION "Hello, World")