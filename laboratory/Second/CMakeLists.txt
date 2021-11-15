add_executable(Second 2.cpp)
target_include_directories(Second PUBLIC ../../LibraryCPP)
target_link_libraries(Second LibraryCPP)
