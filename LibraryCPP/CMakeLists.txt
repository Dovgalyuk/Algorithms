add_library(LibraryCPP STATIC vector.cpp queue.cpp)
target_include_directories(LibraryCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(Tests)