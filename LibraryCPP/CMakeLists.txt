add_library(LibraryCPP STATIC array.cpp list.cpp queue.cpp stack.cpp vector.cpp)

add_subdirectory(Tests)

add_executable(TestFirstTask zadanie1.cpp)
target_link_libraries(TestFirstTask LibraryCPP)

add_executable(TestSecondTask zadanie2.cpp)
target_link_libraries(TestSecondTask LibraryCPP)