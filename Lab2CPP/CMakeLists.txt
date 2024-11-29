cmake_minimum_required(VERSION 3.10)
project(Lab2CPP)

set(CMAKE_CXX_STANDARD 11)

add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_test(NAME TestLab2CPP COMMAND Lab2CPP)