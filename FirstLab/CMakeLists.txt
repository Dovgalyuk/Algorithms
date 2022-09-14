add_executable(FirstLab firstlab.cpp)
target_include_directories(FirstLab PUBLIC ../LibraryCPP)
target_link_libraries(FirstLab LibraryCPP)
