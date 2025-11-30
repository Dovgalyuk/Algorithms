add_library(LibraryCPPClass STATIC array.cpp list.cpp queue.cpp stack.cpp vector.cpp)
target_include_directories(LibraryCPPClass PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})