cmake_minimum_required(VERSION 3.10)
project(Lab_number_1)

# Создаем исполняемый файл для вашей программы
add_executable(program program.c)

# Включаем модуль тестирования
enable_testing()


add_test(NAME Lab_number_1 COMMAND program  input_1.txt input_2.txt input_3.txt)  # Регистрация теста

