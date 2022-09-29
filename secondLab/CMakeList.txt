add_executable(secondLab main.cpp)
target_include_directories(secondLab PUBLIC ../LibraryCPP)
target_link_libraries(secondLab LibraryCPP)
