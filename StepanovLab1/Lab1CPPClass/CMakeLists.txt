cmake_minimum_required(VERSION 3.9) #показывает какой минимальной версией можно собрать проект
project(lab1cppclass) #дает имя проекту
include(CTest)
#дает понять что будет собираться исполняеый файл(exe)
#первый аргумент - это название собираемоего проекта, остальные исходные файлы *.h *.cpp
#все аргументы записываются через пробел
add_library(array STATIC ../LibraryCPPClass/array.cpp)
add_executable(lab1cppclass struct1.cpp)
target_include_directories(lab1cppclass PUBLIC ../LibraryCPPClass)
target_link_libraries(lab1cppclass array)
add_test(NAME TestLab1CPPClass COMMAND lab1cppclass ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPPClass PROPERTY PASS_REGULAR_EXPRESSION "12 4")