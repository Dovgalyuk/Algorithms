cmake_minimum_required(VERSION 3.15)
project(Algorithms)

enable_testing()
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
if (MSVC)
#    needs at least cmake 3.15
<<<<<<< HEAD
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-gnu-empty-struct -Wno-unused-parameter)
=======
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
>>>>>>> 94a05d49d3723788cd34dc027e5e97564b89c957
endif()

#add_subdirectory(LibraryC)
add_subdirectory(LibraryCPP)
#add_subdirectory(LibraryCPPClass)
#add_subdirectory(LibraryCPPTemplate)

#add_subdirectory(Lab1CPP)
add_subdirectory(Lab2CPP)