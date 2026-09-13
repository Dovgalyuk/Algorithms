cmake_minimum_required(VERSION 3.10)
project(LibraryCPP)

add_library(LibraryCPP array.cpp list.cpp queue.cpp stack.cpp vector.cpp)

add_subdirectory(Tests)

target_include_directories(LibraryCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})