add_executable(TestVectorC main.cpp)
target_include_directories(TestVectorC PUBLIC ../LibraryC)
target_link_libraries(TestVectorC LibraryC)
