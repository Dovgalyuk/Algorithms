cmake_minimum_required(VERSION 3.10)
project(LibraryCPPClass)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ArrayLib
    array.cpp
)

target_include_directories(ArrayLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(LibraryCPPClass ALIAS ArrayLib)

enable_testing()

add_executable(TestArray
    Tests/array.cpp
)

target_link_libraries(TestArray PRIVATE ArrayLib)

target_include_directories(TestArray PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_test(NAME Array_basic COMMAND TestArray)
