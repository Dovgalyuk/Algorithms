add_library(LibraryCPP STATIC array.cpp)
add_subdirectory(Tests)
target_include_directories(LibraryCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

