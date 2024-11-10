add_library(LibraryCPP STATIC array.cpp list.cpp queue.cpp stack.cpp vector.cpp)

add_executable(Lab1C lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_subdirectory(Tests)

add_test(NAME TestLab1C COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)