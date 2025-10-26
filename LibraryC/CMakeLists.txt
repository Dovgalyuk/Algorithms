cmake_minimum_required(VERSION 3.15)
add_library(LibraryC STATIC array.c list.c queue.c stack.c vector.c)

add_subdirectory(Tests)
