cmake_minimum_required(VERSION 3.10)
project(Algorithms)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(LibraryCPP)
add_subdirectory(LibraryCPPClass)
add_subdirectory(LibraryCPPTemplate)

add_subdirectory(Lab1CPP)
