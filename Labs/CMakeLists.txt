add_executable(Task1CPP lab1.cpp)
target_include_directories(Task1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Task1CPP LibraryCPP)