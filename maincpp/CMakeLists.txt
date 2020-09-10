add_executable(Maincpp main.cpp)
target_include_directories(Maincpp PUBLIC ../LibraryCPP)
target_link_libraries(Maincpp LibraryCPP)