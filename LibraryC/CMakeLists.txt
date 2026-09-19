add_library(LibraryC STATIC array.c list.c queue.c stack.c vector.c)

if(BUILD_C_EXAMPLE)
    add_subdirectory(Tests)
endif()
