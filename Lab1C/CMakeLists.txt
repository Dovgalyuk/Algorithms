add_executable(Lab1CPP lab1.c)
target_include_directories(Lab1CPP PUBLIC ../LibraryC)
target_link_libraries(Lab1CPP LibraryC)
