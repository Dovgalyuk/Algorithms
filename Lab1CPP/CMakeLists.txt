add_executable(Lab1CPP lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab1CPP LibraryCPPTemplate)