add_library(LibraryCPP STATIC array.cpp list.cpp queue.cpp stack.cpp vector.cpp)


add_executable(HashTableCPP HashTable.cpp)
target_include_directories(HashTableCPP PUBLIC ../LibraryCPPTemplate)

add_subdirectory(Tests)
