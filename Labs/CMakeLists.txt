add_executable(FirstLab first.cpp)
target_include_directories(FirstLab PUBLIC ../LibraryCPP)
target_link_libraries(FirstLab LibraryCPP)
add_test(FirstLab TestArrayCPP)