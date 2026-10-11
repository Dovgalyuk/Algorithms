cmake_minimum_required(VERSION 3.10)
project(Lab2CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем заголовочные файлы из LibraryCPP
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP)

# Собираем исполняемый файл, добавляя исходники vector и stack
add_executable(java_vm 
    java_vm.cpp 
    ../LibraryCPP/vector.cpp 
    ../LibraryCPP/stack.cpp
)

enable_testing()

# Тест 1: Базовый тест из задания
add_test(NAME test1_basic COMMAND java_vm ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1.txt)
set_tests_properties(test1_basic PROPERTIES PASS_REGULAR_EXPRESSION "stack:")

# Тест 2: Арифметика и swap
add_test(NAME test2_arithmetic COMMAND java_vm ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2.txt)
set_tests_properties(test2_arithmetic PROPERTIES PASS_REGULAR_EXPRESSION "stack:")

# Тест 3: Вызов функции (invokestatic/return)
add_test(NAME test3_invoke COMMAND java_vm ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test3.txt)
set_tests_properties(test3_invoke PROPERTIES PASS_REGULAR_EXPRESSION "call 4")

# Тест 4: Ошибка - pop адреса возврата (должен упасть)
add_test(NAME test4_error_pop_return COMMAND java_vm ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test4_error.txt)
set_tests_properties(test4_error_pop_return PROPERTIES WILL_FAIL TRUE)

# Тест 5: Ошибка - return с обычным числом (должен упасть)
add_test(NAME test5_error_return_num COMMAND java_vm ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test5_error.txt)
set_tests_properties(test5_error_return_num PROPERTIES WILL_FAIL TRUE)

# тест 6: Проверка работы с переменными (store/load)
add_test(NAME test6 COMMAND java_vm ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test6.txt)
set_tests_properties(test6 PROPERTIES PASS_REGULAR_EXPRESSION "stack:")

#тест 7: Проверка работы с переменными (store/load) и арифметикой
add_test(NAME test7 COMMAND java_vm ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test7.txt)
set_tests_properties(test7 PROPERTIES PASS_REGULAR_EXPRESSION "vars:")