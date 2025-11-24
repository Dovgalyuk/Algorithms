add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPP LibraryCPPClass)


add_subdirectory(Tests)