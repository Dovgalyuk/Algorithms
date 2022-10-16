add_executable(thirdLab main.cpp)
target_include_directories(thirdLab PUBLIC ../LibraryCPP)
target_link_libraries(thirdLab LibraryCPP)
