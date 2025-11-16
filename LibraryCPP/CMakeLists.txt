#add_library(LibraryCPP STATIC array.cpp) list.cpp queue.cpp stack.cpp vector.cpp)
add_library(LibraryCPP STATIC stack.cpp vector.cpp)

add_subdirectory(Tests)
