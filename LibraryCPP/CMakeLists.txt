add_library(LibraryCPP STATIC array.cpp list.cpp stack.cpp vector.cpp queue.cpp)

target_include_directories(LibraryCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Tests)