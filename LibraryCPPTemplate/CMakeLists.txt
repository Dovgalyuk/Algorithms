cmake_minimum_required(VERSION 3.10)
project(LibraryCPPTemplate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная библиотека (header-only)
add_library(ArrayTemplate INTERFACE)
target_include_directories(ArrayTemplate INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Тесты
add_subdirectory(Tests)