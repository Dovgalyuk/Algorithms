add_library(LibraryCPP STATIC list.cpp stack.cpp)

target_include_directories(LibraryCPP
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(Tests)
