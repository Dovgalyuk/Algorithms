add_executable(SecondLab second.cpp)
target_include_directories(SecondLab PUBLIC ../../LibraryCPP)
target_link_libraries(SecondLab LibraryCPP)