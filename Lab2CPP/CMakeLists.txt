cmake_minimum_required(VERSION 3.16)

project(Lab2CPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(fish
    task.cpp
)

target_include_directories(fish
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP
)

target_link_libraries(fish
    PRIVATE
        LibraryCPP
)

enable_testing()

# тест hello: интерпретатор должен вывести строку Hello, world!
# hello.fish содержит программу на языке Fish, hello.in - пустой файл входных данных
add_test(
    NAME fish_hello
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/hello.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/hello.in
)

set_tests_properties(
    fish_hello
    PROPERTIES
        PASS_REGULAR_EXPRESSION "Hello, world!"
)

# тест пустой программы: скрипт сразу завершается командой ;
# ожидаемый вывод отсутствует
add_test(
    NAME fish_empty
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.in
)

# арифметический тест: программа вычисляет 2 + 3 и выводит результат 5
add_test(
    NAME fish_arithmetic
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/arithmetic.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/arithmetic.in
)

set_tests_properties(
    fish_arithmetic
    PROPERTIES
        PASS_REGULAR_EXPRESSION "5"
)

# тест чтения входных данных: программа считывает символ A из файла a.in и выводит его
add_test(
    NAME fish_a
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/a.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/a.in
)

set_tests_properties(
    fish_a
    PROPERTIES
        PASS_REGULAR_EXPRESSION "A"
)

# тест операций: -, *, ,, %, =, ), (
# test_ops.fish содержит последовательность арифметических и логических операций
add_test(
    NAME fish_ops
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/test_ops.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.in
)

set_tests_properties(
    fish_ops
    PROPERTIES
        PASS_REGULAR_EXPRESSION "3124111"
)

# тест операций со стеком: :, ~, $, @, {, }, r, l
# test_stack.fish содержит операции дублирования, удаления, обмена, перестановки, сдвига и разворота
add_test(
    NAME fish_stack
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/test_stack.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.in
)

set_tests_properties(
    fish_stack
    PROPERTIES
        PASS_REGULAR_EXPRESSION "53242312"
)

# тест потока управления: >, <, ^, v, /, \, _, |, #, x, !, ?
# test_flow.fish содержит цикл с использованием ? для проверки условного перехода
add_test(
    NAME fish_flow
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/test_flow.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.in
)

set_tests_properties(
    fish_flow
    PROPERTIES
        PASS_REGULAR_EXPRESSION "321"
)

# тест шестнадцатеричных цифр: a–f, +, n
# test_hex.fish содержит сложение шестнадцатеричных цифр a (10) и f (15)
add_test(
    NAME fish_hex
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/test_hex.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.in
)

set_tests_properties(
    fish_hex
    PROPERTIES
        PASS_REGULAR_EXPRESSION "25"
)

# тест вычитания с отрицательным результатом: -, n
# test_negative.fish содержит вычитание 3 - 5 = -2
add_test(
    NAME fish_negative
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/test_negative.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.in
)

set_tests_properties(
    fish_negative
    PROPERTIES
        PASS_REGULAR_EXPRESSION "-2"
)

# тест деления: ,, n
# test_division.fish содержит деление 7 / 2 = 3 (целочисленное)
add_test(
    NAME fish_division
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/test_division.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.in
)

set_tests_properties(
    fish_division
    PROPERTIES
        PASS_REGULAR_EXPRESSION "3"
)

# тест остатка от деления: %, n
# test_modulo.fish содержит остаток 10 % 5 = 0
add_test(
    NAME fish_modulo
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/test_modulo.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.in
)

set_tests_properties(
    fish_modulo
    PROPERTIES
        PASS_REGULAR_EXPRESSION "0"
)

# тест равенства: =, n
# test_not_equal.fish содержит проверку 3 = 5 то 0 (ложь)
add_test(
    NAME fish_not_equal
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/test_not_equal.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.in
)

set_tests_properties(
    fish_not_equal
    PROPERTIES
        PASS_REGULAR_EXPRESSION "0"
)

# тест больше: ), n
# test_equal_greater.fish содержит проверку 5 ) 5 то 0 (ложь, не больше)
add_test(
    NAME fish_equal_greater
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/test_equal_greater.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.in
)

set_tests_properties(
    fish_equal_greater
    PROPERTIES
        PASS_REGULAR_EXPRESSION "0"
)

# тест меньше: (, n
# test_equal_less.fish содержит проверку 5 ( 5 то 0 (ложь, не меньше)
add_test(
    NAME fish_equal_less
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/test_equal_less.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.in
)

set_tests_properties(
    fish_equal_less
    PROPERTIES
        PASS_REGULAR_EXPRESSION "0"
)

# тест строкового режима с одинарными кавычками: ', o
# test_string_single.fish содержит строку 'Hi' в одинарных кавычках и вывод iH
add_test(
    NAME fish_string_single
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/test_string_single.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.in
)

set_tests_properties(
    fish_string_single
    PROPERTIES
        PASS_REGULAR_EXPRESSION "iH"
)

# тест деления на ноль: ,, ошибка
# test_division_zero.fish содержит деление 1 / 0, которое должно вызвать ошибку
add_test(
    NAME fish_division_zero
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/test_division_zero.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.in
)

set_tests_properties(
    fish_division_zero
    PROPERTIES
#        WILL_FAIL TRUE
        PASS_REGULAR_EXPRESSION "деление на ноль"
)

# тест остатка от деления на ноль: %, ошибка
# test_modulo_zero.fish содержит остаток 1 % 0, которое должно вызвать ошибку
add_test(
    NAME fish_modulo_zero
    COMMAND fish
        ${CMAKE_CURRENT_SOURCE_DIR}/test_modulo_zero.fish
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.in
)

set_tests_properties(
    fish_modulo_zero
    PROPERTIES
#        WILL_FAIL TRUE
        PASS_REGULAR_EXPRESSION "деление по модулю на ноль"
)