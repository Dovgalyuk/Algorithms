add_library(LibraryCPP STATIC array.cpp list.cpp queue.cpp stack.cpp vector.cpp)
target_include_directories(LibraryCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Tests)
