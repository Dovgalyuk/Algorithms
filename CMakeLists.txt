cmake_minimum_required(VERSION 3.15)
project(Algorithms)

enable_testing()

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-gnu-empty-struct -Wno-unused-parameter)
endif()

add_subdirectory(LibraryCPPTemplate)
add_subdirectory(Lab4CPP)
