add_executable(first test.cpp)
target_include_directories(first PUBLIC ../LibraryCPP)
target_link_libraries(first LibraryCPP)