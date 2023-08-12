cmake_minimum_required(VERSION 3.0)
project(Algorithms)

enable_testing()
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(LibraryC)
add_subdirectory(LibraryCPP)
add_subdirectory(LibraryCPPTemplate)
