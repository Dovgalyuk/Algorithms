add_executable(lab2dCPP lab2d.cpp)
target_include_directories(lab2dCPP PUBLIC ../LibraryCPP)
target_link_libraries(lab2dCPP LibraryCPP)

add_executable(lab3dCPP lab3d.cpp)
target_include_directories(lab3dCPP PUBLIC ../LibraryCPP)
target_link_libraries(lab3dCPP LibraryCPP)
