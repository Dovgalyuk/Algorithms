cmake_minimum_required(VERSION 3.15)
project(Algorithms)


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/LibraryC
    ${CMAKE_CURRENT_SOURCE_DIR}/LibraryCPP
    ${CMAKE_CURRENT_SOURCE_DIR}/LibraryCPPClass
    ${CMAKE_CURRENT_SOURCE_DIR}/LibraryCPPTemplate
)

enable_testing()
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
if (MSVC)
    # needs at least cmake 3.15
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-gnu-empty-struct -Wno-unused-parameter)
endif()

add_subdirectory(LibraryC)
add_subdirectory(LibraryCPP)
add_subdirectory(LibraryCPPClass)
add_subdirectory(LibraryCPPTemplate)

add_subdirectory(Lab1C)
