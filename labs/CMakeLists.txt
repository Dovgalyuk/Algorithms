add_executable(labs lab1d.cpp)
target_include_directories(labs PUBLIC ../LibraryCPP)
target_link_libraries(labs LibraryCPP)

add_executable(labs lab2d.cpp)
target_include_directories(labs PUBLIC ../LibraryCPP)
target_link_libraries(labs LibraryCPP)

add_executable(labs lab3d.cpp)
target_include_directories(labs PUBLIC ../LibraryCPP)
target_link_libraries(labs LibraryCPP)
