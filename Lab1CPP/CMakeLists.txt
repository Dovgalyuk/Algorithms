cmake_minimum_required(VERSION 3.16)

project(Prac1NonBob LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_app test.cpp)
add_executable(fibonacci_app fibonacci.cpp)
add_executable(unique_app unique.cpp)

enable_testing()

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/input_fib.txt" "10\n")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/input_unique.txt" "8\n10 500 10 999 500 0 42 0\n")

add_test(NAME ContainerTest COMMAND test_app)

add_test(NAME FibonacciTest COMMAND fibonacci_app)
set_tests_properties(FibonacciTest PROPERTIES PASS_REGULAR_EXPRESSION "0 1 1 2 3 5 8 13 21 34")

add_test(NAME UniqueTest COMMAND unique_app)
set_tests_properties(UniqueTest PROPERTIES PASS_REGULAR_EXPRESSION "999 42")

include(GNUInstallDirs)
install(TARGETS test_app fibonacci_app unique_app
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
