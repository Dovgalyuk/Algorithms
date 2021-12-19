add_executable(Fourth 4.cpp)
target_include_directories(Fourth PUBLIC ../../LibraryCPP)
target_link_libraries(Fourth LibraryCPP)
