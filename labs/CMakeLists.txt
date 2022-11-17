add_executable(lab1dCPP lab1d.cpp)
target_include_directories(lab1d.cpp PUBLIC ../LibraryCPP)
target_link_libraries(lab1d.cpp LibraryCPP)
