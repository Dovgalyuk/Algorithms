cmake_minimum_required(VERSION 3.10)
project(ContainersLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включить тестирование
enable_testing()

# Основные цели
add_subdirectory(Lab1C)
add_subdirectory(LibraryCPPTemplate)