cmake_minimum_required(VERSION 3.15)
project(Lab1CPP LANGUAGES CXX)

add_executable(Lab1_Fibonacci fibonacci.cpp)
target_include_directories(Lab1_Fibonacci PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1_Fibonacci LibraryCPPClass)

add_executable(Lab1_Unique unique.cpp)
target_include_directories(Lab1_Unique PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1_Unique LibraryCPPClass)

enable_testing()

add_test(NAME Fib_10 COMMAND Lab1_Fibonacci "${CMAKE_CURRENT_SOURCE_DIR}/input_fib1.txt")
set_property(TEST Fib_10 PROPERTY PASS_REGULAR_EXPRESSION "0 1 1 2 3 5 8 13 21 34")

add_test(NAME Fib_5 COMMAND Lab1_Fibonacci "${CMAKE_CURRENT_SOURCE_DIR}/input_fib2.txt")
set_property(TEST Fib_5 PROPERTY PASS_REGULAR_EXPRESSION "0 1 1 2 3")

add_test(NAME Unique_1 COMMAND Lab1_Unique "${CMAKE_CURRENT_SOURCE_DIR}/input_unique1.txt")
set_property(TEST Unique_1 PROPERTY PASS_REGULAR_EXPRESSION "999 42")

add_test(NAME Unique_2 COMMAND Lab1_Unique "${CMAKE_CURRENT_SOURCE_DIR}/input_unique2.txt")
set_property(TEST Unique_2 PROPERTY PASS_REGULAR_EXPRESSION "3 1000")
