add_executable(Lab1C lab1.c)
target_include_directories(Lab1C PUBLIC ../LibraryC)
target_link_libraries(Lab1C LibraryC)

# Основной тест 
add_test(NAME TestLab1C_Basic COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1C_Basic PROPERTY PASS_REGULAR_EXPRESSION "function_calls: 5")

# Тест арифметических операций
add_test(NAME TestLab1C_Arithmetic COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test_arithmetic.txt)
set_property(TEST TestLab1C_Arithmetic PROPERTY PASS_REGULAR_EXPRESSION "function_calls: 8")

# Тест работы с переменными
add_test(NAME TestLab1C_Variables COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test_variables.txt)
set_property(TEST TestLab1C_Variables PROPERTY PASS_REGULAR_EXPRESSION "function_calls: 12")

# Тест побитовых операций
add_test(NAME TestLab1C_Bitwise COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test_bitwise.txt)
set_property(TEST TestLab1C_Bitwise PROPERTY PASS_REGULAR_EXPRESSION "function_calls: 8")

# Тест операции swap
add_test(NAME TestLab1C_Swap COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test_swap.txt)
set_property(TEST TestLab1C_Swap PROPERTY PASS_REGULAR_EXPRESSION "function_calls: 6")

# Тест вызовов функций
add_test(NAME TestLab1C_Functions COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test_functions.txt)
set_property(TEST TestLab1C_Functions PROPERTY PASS_REGULAR_EXPRESSION "function_calls: 6")

# Тест обработки ошибок
add_test(NAME TestLab1C_Errors COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test_errors.txt)
set_property(TEST TestLab1C_Errors PROPERTY PASS_REGULAR_EXPRESSION "Error:")
