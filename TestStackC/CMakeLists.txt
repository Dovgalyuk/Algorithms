add_executable(TestStackC main.cpp)
target_include_directories(TestStackC PUBLIC ../LibraryC)
target_link_libraries(TestStackC LibraryC)
