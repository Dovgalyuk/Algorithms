add_library(LibraryCPP STATIC filter_bloom.cpp)
add_subdirectory(Tests)
target_include_directories(LibraryCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

