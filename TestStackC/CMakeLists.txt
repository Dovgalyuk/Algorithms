add_executable(TestStackC main.cpp)
target_include_directories(TestStackC PUBLIC ../LibraryCPP)
target_link_libraries(TestStackC LibraryCPP)
