add_executable(LibraryMy Individual.cpp)
target_include_directories(LibraryMy PUBLIC ../LibraryCPP)
target_link_libraries(LibraryMy LibraryCPP)