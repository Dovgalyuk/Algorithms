add_library(LibraryCPPClass STATIC array.cpp list.cpp queue.cpp stack.cpp vector.cpp)
target_include_directories(LibraryCPPClass PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(LibraryCPPClassString STATIC array.cpp list.cpp queue.cpp stack.cpp vector.cpp)
target_include_directories(LibraryCPPClassString PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(LibraryCPPClassString PUBLIC USE_STRING_DATA)

add_subdirectory(Tests)
