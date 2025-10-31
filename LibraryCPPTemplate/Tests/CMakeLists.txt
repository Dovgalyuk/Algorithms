cmake_minimum_required(VERSION 3.10)

# Тест для array
add_executable(test_array array.cpp)
target_link_libraries(test_array ArrayTemplate)

add_test(NAME ArrayTemplateTest COMMAND test_array)