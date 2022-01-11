cmake_minimum_required(VERSION 3.0)
project(lab4)

add_executable(lab4 Test.cpp)
target_include_directories(lab4 PUBLIC ../LibraryCPP)
target_link_libraries(lab4 LibraryCPP)
