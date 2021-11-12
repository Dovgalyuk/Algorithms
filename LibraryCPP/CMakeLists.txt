add_library(LibraryCPP STATIC array.cpp list.cpp queue.cpp stack.cpp vector.cpp)

add_subdirectory(Tests)
add_executable(Second 2.cpp)
target_link_libraries(Second LibraryCPP)
