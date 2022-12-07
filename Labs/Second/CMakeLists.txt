add_executable(Second lab2.cpp)
target_include_directories(Second PUBLIC ../../LibraryCPP)
target_link_libraries(Second LibraryCPP)