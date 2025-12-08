add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab3CPP LibraryCPPClass)

add_subdirectory(Tests)