add_executable(MyLabs First.cpp)
target_include_directories(MyLabs PUBLIC ../LibraryCPP)
target_link_libraries(MyLabs LibraryCPP)