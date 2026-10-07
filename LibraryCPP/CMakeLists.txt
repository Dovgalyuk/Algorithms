add_library(LibraryCPP STATIC array.cpp list.cpp queue.cpp stack.cpp vector.cpp)
target_compile_features(LibraryCPP PUBLIC cxx_std_11)

add_subdirectory(Tests)
