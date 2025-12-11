add_library(LibraryCPPTemplate INTERFACE)
target_include_directories(LibraryCPPTemplate INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
add_subdirectory(Tests)
