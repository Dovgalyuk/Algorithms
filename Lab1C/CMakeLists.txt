cmake_minimum_required(VERSION 3.10)
project(array_tasks)

set(CMAKE_C_STANDARD 11)

add_executable(array_tasks main.c array.c)

# Добавляем тест
enable_testing()

add_test(NAME array_test
         COMMAND array_tasks ${CMAKE_SOURCE_DIR}/input.txt)
