add_executable(lab1CPP lab1.cpp)
target_include_directories(lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(lab1CPP LibraryCPP)
