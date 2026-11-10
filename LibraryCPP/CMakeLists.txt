add_library(LibraryCPP STATIC array.cpp list.cpp queue.cpp stack.cpp vector.cpp avl.cpp)

if(MSVC)
    target_compile_options(LibraryCPP PRIVATE /utf-8)
endif()

add_subdirectory(Tests)
