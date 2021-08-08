add_executable(TestVectorC main.cpp)
target_include_directories(TestVectorC PUBLIC ../LibraryC)
target_link_libraries(TestVectorC LibraryC)

add_test(TestVectorC TestVectorC)

set_tests_properties(TestVectorC
    PROPERTIES TIMEOUT 10)
