add_executable(Lab1dCPP Lab1d.cpp)
target_include_directories(Lab1d.cpp PUBLIC ../LibraryCPP)
target_link_libraries(Lab1d.cpp LibraryCPP)
