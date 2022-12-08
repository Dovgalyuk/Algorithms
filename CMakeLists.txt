cmake_minimum_required(VERSION 3.0)

project(Algorithms)



enable_testing()



add_subdirectory(LibraryC)

add_subdirectory(LibraryCPP)

add_subdirectory(LibraryCPPTemplate)
add_executable(LAB1 lab1.cpp)
target_include_directories(LAB1 PUBLIC ../LibraryCPP)
target_link_libraries(LAB1 LibraryCPP)
