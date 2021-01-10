add_executable(TestVectorC main.cpp)
target_include_directories(TestVectorC PUBLIC ../LibraryCPP)
target_link_libraries(TestVectorC LibraryCPP)