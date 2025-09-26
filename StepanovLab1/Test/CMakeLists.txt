cmake_minimum_required(VERSION 3.9)
project(lab1test)
include(CTest)

add_library(array STATIC ../LibraryCPPClass/array.cpp)
add_executable(lab1test array.cpp)
target_include_directories(lab1test  PUBLIC ../LibraryCPPClass)
target_link_libraries(lab1test array)
add_test(NAME TestArrayCPPClass COMMAND lab1test)
