cmake_minimum_required(VERSION 3.10)

project(MyArrayProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR})


set(SOURCES
    labb.cpp
    array.cpp # Добавьте сюда ваш файл реализации массива, если он есть
)


add_executable(MyArrayProgram ${SOURCES})
