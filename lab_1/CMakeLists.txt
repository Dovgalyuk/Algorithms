# Указываем минимальную версию CMake
cmake_minimum_required(VERSION 3.10)

# Указываем имя проекта и его версию
project(MyArrayProject VERSION 1.0)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем директорию, где находятся заголовочные файлы
include_directories(${CMAKE_SOURCE_DIR})

# Указываем исходные файлы вашего проекта
set(SOURCES
    main.cpp
    array.cpp # Добавьте сюда ваш файл реализации массива, если он есть
)

# Создаем исполняемый файл из исходных файлов
add_executable(MyArrayProgram ${SOURCES})
