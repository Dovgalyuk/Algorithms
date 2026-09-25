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