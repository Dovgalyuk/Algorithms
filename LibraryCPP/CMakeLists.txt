cmake_minimum_required(VERSION 3.15)
project(LibraryCPP)
add_library(LibraryCPP STATIC array.cpp)
target_include_directories(LibraryCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(Tests)


