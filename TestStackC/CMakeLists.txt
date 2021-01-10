add_executable(TestStackC main.cpp)
target_include_directories(TestStackC PUBLIC ../LibraryCPPTemplate)
target_link_libraries(TestStackC LibraryCPPTemplate)
