cmake_minimum_required(VERSION 3.0)

project(Algorithms)

enable_testing()
add_executable(TestCPP list.cpp)
target_include_directories(TestCPP PUBLIC ..)
target_link_libraries(TestCPP LibraryCPP)
add_test(TestListCPP TestCPP)
add_subdirectory(LibraryC)
add_subdirectory(LibraryCPP)
add_subdirectory(LibraryCPPTemplate)
add_subdirectory(LabTasks)