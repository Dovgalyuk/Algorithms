add_executable(Third main.cpp)
target_include_directories(Third PUBLIC ../LibraryCPP)
target_link_libraries(Third LibraryCPP) 