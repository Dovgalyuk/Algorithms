cmake_minimum_required(VERSION 3.15)
project(Algorithms)

enable_testing()
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
if (MSVC)
    # needs at least cmake 3.15
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-gnu-empty-struct -Wno-unused-parameter)
endif()

configure_file(
    ${CMAKE_SOURCE_DIR}/Lab1C/input.txt
    ${CMAKE_BINARY_DIR}/Testing/Temporary/input.txt
    COPYONLY
)
add_subdirectory(LibraryC)
# add_subdirectory(LibraryCPP)
# add_subdirectory(LibraryCPPClass)
# add_subdirectory(LibraryCPPTemplate)

add_subdirectory(Lab1C)
