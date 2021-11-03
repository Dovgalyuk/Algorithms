cmake_minimum_required(VERSION 3.0)

add_executable(lab1 SomeCode.cpp)
target_include_directories(lab1 PUBLIC ../LibraryCPP)
target_link_libraries(lab1 LibraryCPP)