add_library(LibraryCPP STATIC array.cpp ${CMAKE_SOURCE_DIR}/LibraryCPPTemplate/array.h list.cpp queue.cpp stack.cpp vector.cpp directed_graph.cpp associative_array.cpp)

add_subdirectory(Tests)
