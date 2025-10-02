cmake_minimum_required(VERSION 3.15)
project(Algorithms LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем систему тестирования ДО подключения поддиректорий
enable_testing()

# Подключаем библиотеку и тесты
add_subdirectory(LibraryCPP)

# Подключаем лабораторную работу
add_subdirectory(Lab1Cpp)
