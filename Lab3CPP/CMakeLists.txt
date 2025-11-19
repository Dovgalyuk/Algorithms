cmake_minimum_required(VERSION 3.10)
project(Lab3CPP)

set(CMAKE_CXX_STANDARD 11)

add_executable(Lab3CPP main.cpp)

target_link_libraries(Lab3CPP LibraryCPP)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)

configure_file(input.txt input.txt COPYONLY)

enable_testing()
add_test(NAME Lab3CPP_Test
         COMMAND Lab3CPP input.txt output.txt
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})