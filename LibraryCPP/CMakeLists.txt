add_library(LibraryCPP STATIC array.cpp list.cpp queue.cpp stack.cpp vector.cpp)
target_include_directories(LibraryCPP PUBLIC /)

add_subdirectory(Tests)
