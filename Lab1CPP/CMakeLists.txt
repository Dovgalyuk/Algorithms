cmake_minimum_required(VERSION 3.15)
project(Lab1CPP)
# Создание исполняемого файла
add_executable(Lab1CPP main.cpp)
# Указываем, где искать заголовочные файлы LibraryCPP
include_directories(${CMAKE_SOURCE_DIR}/../LibraryCPP)
# Добавляем саму библиотеку
target_link_libraries(Lab1CPP PRIVATE ${CMAKE_SOURCE_DIR}/../LibraryCPP/build/libLibraryCPP.a)
# Добавляем тест, передавая input.txt как аргумент командной строки
enable_testing()
add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)