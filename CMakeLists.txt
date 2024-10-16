cmake_minimum_required(VERSION 3.15)
project(Algorithms)

enable_testing()
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
if (MSVC)
    # needs at least cmake 3.15
    add_compile_options(/W4 /WX /Wv:18)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-gnu-empty-struct -Wno-unused-parameter)
endif()

add_subdirectory(LibraryC)
add_subdirectory(Lab1C)

set_target_properties(Lab1C PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)