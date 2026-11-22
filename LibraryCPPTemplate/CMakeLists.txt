cmake_minimum_required(VERSION 3.10)
project(LibraryCPPTemplate)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Заголовочная библиотека графов (шаблоны + inline-реализация)
add_library(LibraryCPPTemplate INTERFACE)
target_include_directories(LibraryCPPTemplate INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(LibraryCPPTemplate INTERFACE LibraryCPP)

add_subdirectory(Tests)
