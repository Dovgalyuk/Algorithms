project(LibraryCPPTemplate)

# Библиотека заголовков (header-only)
add_library(LibraryCPPTemplate INTERFACE)
target_include_directories(LibraryCPPTemplate INTERFACE .)

add_subdirectory(Tests)