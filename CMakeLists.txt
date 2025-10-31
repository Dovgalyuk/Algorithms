cmake_minimum_required(VERSION 3.10)
project(ContainersLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
if (MSVC)
    # needs at least cmake 3.15
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror -Wpedantic -Wno-unused-parameter -ftrapv)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options(-fsanitize=address,undefined)
        add_link_options(-fsanitize=address,undefined)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(-fsanitize=address,undefined,leak)
        add_link_options(-fsanitize=address,undefined,leak)
    endif()
endif()

# Основные цели
add_subdirectory(Lab1C)
add_subdirectory(LibraryCPPTemplate)
