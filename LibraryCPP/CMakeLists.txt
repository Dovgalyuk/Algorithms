add_library(LibraryCPP STATIC queue.cpp vector.cpp)
add_subdirectory(Tests)
target_include_directories(LibraryCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})