add_executable(LibraryCPP lab1.cpp)
target_include_directories(LibraryCPP PUBLIC ../LibraryCPP)
target_link_libraries(LibraryCPP LibraryCPP)
