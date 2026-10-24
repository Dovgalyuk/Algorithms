cmake_minimum_required(VERSION 3.10)
project(LibraryCPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(LibraryCPP
    array.cpp
    list.cpp
    queue.cpp
    stack.cpp
    vector.cpp
)

target_include_directories(LibraryCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
