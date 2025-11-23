add_executable(Lab2C lab2.c interpreter.c)
target_include_directories(Lab2C PUBLIC ../LibraryC)
target_link_libraries(Lab2C LibraryC)

add_test(NAME TestLab2C_01_Push
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_01_push_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_01_push_input.txt)
set_property(TEST TestLab2C_01_Push PROPERTY PASS_REGULAR_EXPRESSION "C.*B.*A")

add_test(NAME TestLab2C_02_RemoveBottom
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_02_remove_bottom_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_02_remove_bottom_input.txt)
set_property(TEST TestLab2C_02_RemoveBottom PROPERTY PASS_REGULAR_EXPRESSION "C.*B")

add_test(NAME TestLab2C_03_Output
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_03_output_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_03_output_input.txt)
set_property(TEST TestLab2C_03_Output PROPERTY PASS_REGULAR_EXPRESSION "Hello")

add_test(NAME TestLab2C_04_Tilde
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_04_tilde_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_04_tilde_input.txt)
set_property(TEST TestLab2C_04_Tilde PROPERTY PASS_REGULAR_EXPRESSION "X")

add_test(NAME TestLab2C_05_ClearTilde
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_05_clear_tilde_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_05_clear_tilde_input.txt)
set_property(TEST TestLab2C_05_ClearTilde PROPERTY PASS_REGULAR_EXPRESSION "A")

add_test(NAME TestLab2C_06_Reverse
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_06_reverse_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_06_reverse_input.txt)
set_property(TEST TestLab2C_06_Reverse PROPERTY PASS_REGULAR_EXPRESSION "A.*B.*C")

add_test(NAME TestLab2C_07_Concat
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_07_concat_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_07_concat_input.txt)
set_property(TEST TestLab2C_07_Concat PROPERTY PASS_REGULAR_EXPRESSION "Hello")

add_test(NAME TestLab2C_08_Jump
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_08_jump_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_08_jump_input.txt)
set_property(TEST TestLab2C_08_Jump PROPERTY PASS_REGULAR_EXPRESSION "C.*A")

add_test(NAME TestLab2C_09_IfTrue
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_09_if_true_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_09_if_true_input.txt)
set_property(TEST TestLab2C_09_IfTrue PROPERTY PASS_REGULAR_EXPRESSION "After.*Match.*A")

add_test(NAME TestLab2C_10_NestedIf
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_10_nested_if_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_10_nested_if_input.txt)
set_property(TEST TestLab2C_10_NestedIf PROPERTY PASS_REGULAR_EXPRESSION "After.*A")

add_test(NAME TestLab2C_11_IfFalse
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_11_if_false_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_11_if_false_input.txt)
set_property(TEST TestLab2C_11_IfFalse PROPERTY PASS_REGULAR_EXPRESSION "After.*A")

add_test(NAME TestLab2C_12_IfNotTrue
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_12_ifnot_true_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_12_ifnot_true_input.txt)
set_property(TEST TestLab2C_12_IfNotTrue PROPERTY PASS_REGULAR_EXPRESSION "After.*NotEqual.*A")

add_test(NAME TestLab2C_13_IfNotFalse
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_13_ifnot_false_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_13_ifnot_false_input.txt)
set_property(TEST TestLab2C_13_IfNotFalse PROPERTY PASS_REGULAR_EXPRESSION "After.*A")

add_test(NAME TestLab2C_14_CreateVar
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_14_create_var_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_14_create_var_input.txt)
set_property(TEST TestLab2C_14_CreateVar PROPERTY PASS_REGULAR_EXPRESSION "Test.*World.*Hello")

add_test(NAME TestLab2C_15_TildeGetVar
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_15_tilde_get_var_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_15_tilde_get_var_input.txt)
set_property(TEST TestLab2C_15_TildeGetVar PROPERTY PASS_REGULAR_EXPRESSION "Hello")

add_test(NAME TestLab2C_16_DeleteVar
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_16_delete_var_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_16_delete_var_input.txt)
set_property(TEST TestLab2C_16_DeleteVar PROPERTY PASS_REGULAR_EXPRESSION "First")

add_test(NAME TestLab2C_17_Math
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_17_math_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_17_math_input.txt)
set_property(TEST TestLab2C_17_Math PROPERTY PASS_REGULAR_EXPRESSION "8")

add_test(NAME TestLab2C_18_GetVar
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_18_get_var_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_18_get_var_input.txt)
set_property(TEST TestLab2C_18_GetVar PROPERTY PASS_REGULAR_EXPRESSION "Hello.*Hello")

add_test(NAME TestLab2C_19_Halt
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_19_halt_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_19_halt_input.txt)
set_property(TEST TestLab2C_19_Halt PROPERTY PASS_REGULAR_EXPRESSION "Before")
set_property(TEST TestLab2C_19_Halt PROPERTY FAIL_REGULAR_EXPRESSION "After")

add_test(NAME TestLab2C_20_Input
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_20_input_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_20_input_input.txt)
set_property(TEST TestLab2C_20_Input PROPERTY PASS_REGULAR_EXPRESSION "Top.*Bottom")

add_test(NAME TestLab2C_21_Random
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_21_random_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_21_random_input.txt)
set_property(TEST TestLab2C_21_Random PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME TestLab2C_22_ClearOutput
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_22_clear_output_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_22_clear_output_input.txt)
set_property(TEST TestLab2C_22_ClearOutput PROPERTY PASS_REGULAR_EXPRESSION "After")

add_test(NAME TestLab2C_23_ReplaceVar
         COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_23_replace_var_script.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_23_replace_var_input.txt)
set_property(TEST TestLab2C_23_ReplaceVar PROPERTY PASS_REGULAR_EXPRESSION "New")
