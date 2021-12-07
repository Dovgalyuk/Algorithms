add_executable(ThirdLab Third.cpp)
target_include_directories(ThirdLab PUBLIC ../../LibraryCPP)
target_link_libraries(ThirdLab LibraryCPP)