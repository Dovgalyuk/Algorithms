add_executable(Machin machine.cpp)
target_include_directories(Machin PUBLIC ../LibraryCPP)
target_link_libraries(Machin LibraryCPP)

add_subdirectory(tests)