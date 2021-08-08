add_executable(TestArrayC main.cpp)
target_include_directories(TestArrayC PUBLIC ../LibraryC)
target_link_libraries(TestArrayC LibraryC)

add_test(TestArrayC TestArrayC)
