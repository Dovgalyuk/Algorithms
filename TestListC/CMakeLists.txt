add_executable(TestListC main.cpp)
target_include_directories(TestListC PUBLIC ../LibraryC)
target_link_libraries(TestListC LibraryC)
