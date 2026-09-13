cmake_minimum_required(VERSION 3.15)

project(Lab1C)

enable_testing()

add_subdirectory(../LibraryC LibraryC_build)

add_executable(Lab1C lab1.c)

target_include_directories(Lab1C PUBLIC ../LibraryC)

target_link_libraries(Lab1C LibraryC)

add_test(NAME TestLab1C
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
)

set_property(
    TEST TestLab1C
    PROPERTY PASS_REGULAR_EXPRESSION "1 4 0 0"
)

add_test(NAME Test1
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt
)

set_property(
    TEST Test1
   
    PROPERTY PASS_REGULAR_EXPRESSION "1 4 0 0"
)
add_test(NAME Test2
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt
)

set_property(
    TEST Test2
    PROPERTY PASS_REGULAR_EXPRESSION "5 25 0 0 0"
)

add_test(NAME Test3
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt
)

set_property(
    TEST Test3
    PROPERTY PASS_REGULAR_EXPRESSION "0 0 0 0 0 0"
)