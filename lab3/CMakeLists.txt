cmake_minimum_required(VERSION 3.0)
project(lab3)

add_executable(lab3 Labirintum.cpp)
target_include_directories(lab3 PUBLIC ../LibraryCPP)
target_link_libraries(lab3 LibraryCPP)
