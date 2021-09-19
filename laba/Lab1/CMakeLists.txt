add_executable(laba lab1.cpp)
target_include_directories(laba PUBLIC ../../LibraryCPP)
target_link_libraries(laba LibraryCPP)