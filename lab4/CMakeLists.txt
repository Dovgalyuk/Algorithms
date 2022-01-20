cmake_minimum_required(VERSION 3.0)
project(lab4)

add_executable(lab4 Prima.cpp)
target_include_directories(lab4 PUBLIC ../LibraryCPP)
target_include_directories(lab4 PUBLIC ../LibraryCPPTemplate)
target_link_libraries(lab4 LibraryCPP)
