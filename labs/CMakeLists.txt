add_executable(labs lab3d.cpp)
target_include_directories(labs PUBLIC ../LibraryCPP)
target_link_libraries(labs LibraryCPP)
