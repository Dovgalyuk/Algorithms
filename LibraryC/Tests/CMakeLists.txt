add_executable(TestArrayC array.cpp)
target_include_directories(TestArrayC PUBLIC ..)
target_link_libraries(TestArrayC LibraryC)
add_test(TestArrayC TestArrayC)

