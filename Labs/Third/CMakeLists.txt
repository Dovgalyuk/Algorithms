add_executable(Third lab3.cpp)
target_include_directories(Third PUBLIC ../../LibraryCPP)
target_link_libraries(Third LibraryCPP)