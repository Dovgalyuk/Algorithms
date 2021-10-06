add_library(LibraryCPP STATIC array.cpp list.cpp queue.cpp stack.cpp vector.cpp test.cpp)
add_executable(first test.cpp)
add_subdirectory(Tests)
