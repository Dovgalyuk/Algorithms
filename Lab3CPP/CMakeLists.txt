cmake_minimum_required(VERSION 3.14)
project(Lab3CPP)

include_directories(${CMAKE_SOURCE_DIR}/LibraryCPP)

add_executable(Lab3CPP main.cpp)
target_link_libraries(Lab3CPP PRIVATE LibraryCPP)

enable_testing()

add_test(NAME radix_sort_example
    COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/Lab3CPP < ${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
)

set_tests_properties(radix_sort_example PROPERTIES
    PASS_REGULAR_EXPRESSION "1 4 5 6 8"
)
