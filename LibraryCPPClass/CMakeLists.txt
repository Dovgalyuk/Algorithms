#add_library(LibraryCPPClass STATIC array.cpp list.cpp queue.cpp stack.cpp vector.cpp "Map.cpp" "Map.h""Tests/Map.cpp"")
add_library(LibraryCPPClass STATIC Map.cpp)
add_subdirectory(Tests)
