add_executable(lab1dCPP lab1d.cpp)
target_include_directories(lab1d.cpp PUBLIC ../LibraryCPP)
target_link_libraries(lab1d.cpp LibraryCPP)

add_executable(lab2dCPP lab2d.cpp)
target_include_directories(lab2d.cpp PUBLIC ../LibraryCPP)
target_link_libraries(lab2d.cpp LibraryCPP)
