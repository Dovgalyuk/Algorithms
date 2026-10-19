cmake_minimum_required(VERSION 3.10)
project(LibraryCPP CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Создаем библиотеку из ваших контейнеров C++
add_library(LibraryCPP list.cpp queue.cpp stack.cpp vector.cpp)
target_include_directories(LibraryCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 2. Включаем поддержку тестирования
enable_testing()

# 3. Собираем исполняемый файл лабиринта (основная программа)
add_executable(library_cpp_main main.cpp)
# Линкуем основную программу с нашей библиотекой контейнеров
target_link_libraries(library_cpp_main PRIVATE LibraryCPP)

# 4. Подключаем папку с тестами
add_subdirectory(Tests)
