cmake_minimum_required(VERSION 3.0)

project(lab2)
add_executable(lab2 SomeCode.cpp)
target_include_directories(lab2 PUBLIC ../LibraryCPP/stack.h)
target_link_libraries(lab2 LibraryCPP)