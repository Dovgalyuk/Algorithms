add_executable(TestListC main.cpp)
target_include_directories(TestListC PUBLIC ../LibraryCPPTemplate)
target_link_libraries(TestListC LibraryCPPTemplate)
