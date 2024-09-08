cmake_minimum_required(VERSION 3.10)
project(Lab_number_1)

# Создаем исполняемый файл для вашей программы
add_executable(program program.c)

# Включаем модуль тестирования
enable_testing()

# Добавляем тесты
add_test(NAME TestLab1_1C COMMAND program ${CMAKE_CURRENT_SOURCE_DIR}/input_1.txt)
add_test(NAME TestLab1_2C COMMAND program ${CMAKE_CURRENT_SOURCE_DIR}/input_2.txt)
add_test(NAME TestLab1_3C COMMAND program ${CMAKE_CURRENT_SOURCE_DIR}/input_3.txt)

