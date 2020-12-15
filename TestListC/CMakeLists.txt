add_executable(TestListC main.cpp)
target_include_directories(TestListC PUBLIC ../LibraryCPP)
target_link_libraries(TestListC LibraryCPP)
