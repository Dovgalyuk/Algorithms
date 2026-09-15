add_library(LibraryCPP INTERFACE)

target_include_directories(LibraryCPP INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Tests)