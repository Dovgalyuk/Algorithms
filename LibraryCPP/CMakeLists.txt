add_library(LibraryCPP STATIC array.cpp list.cpp queue.cpp stack.cpp vector.cpp)

add_subdirectory(Tests)
target_include_directories(test PRIVATE ${conio.h})
