add_executable(First main.cpp)
target_include_directories(First PUBLIC ../LibraryCPP)
target_link_libraries(First LibraryCPP)
