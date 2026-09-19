cmake_minimum_required(VERSION 3.15)
project(Algorithms)

enable_testing()
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
if (MSVC)
    # needs at least cmake 3.15
    # Match -Wno-unused-parameter for the unfinished container templates.
    add_compile_options(/W4 /WX /wd4100)
else()
    add_compile_options(-Wall -Wextra -Werror -Wpedantic -Wno-gnu-empty-struct -Wno-unused-parameter -ftrapv)
    if (NOT WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options(-fsanitize=address,undefined)
        add_link_options(-fsanitize=address,undefined)
    elseif (NOT WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(-fsanitize=address,undefined,leak)
        add_link_options(-fsanitize=address,undefined,leak)
    endif()
endif()

option(BUILD_C_EXAMPLE "Build unfinished C template tests and Lab1C example" OFF)

add_subdirectory(LibraryC)
add_subdirectory(LibraryCPP)
add_subdirectory(LibraryCPPClass)
add_subdirectory(LibraryCPPTemplate)

if(BUILD_C_EXAMPLE)
    add_subdirectory(Lab1C)
endif()

add_subdirectory(LAB_1)
