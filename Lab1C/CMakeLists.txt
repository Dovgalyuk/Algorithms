cmake_minimum_required(VERSION 3.15)

project(Lab1C)

enable_testing()

add_executable(Task1 task1.c)

target_include_directories(Task1 PUBLIC ../LibraryC)

target_link_libraries(Task1 LibraryC)


add_executable(Task2 task2.c)

target_include_directories(Task2 PUBLIC ../LibraryC)

target_link_libraries(Task2 LibraryC)


add_test(NAME Task1Test1
    COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/task1test1.txt
)

set_property(
    TEST Task1Test1
    PROPERTY PASS_REGULAR_EXPRESSION "1 3 5"
)


add_test(NAME Task1Test2
    COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/task1test2.txt
)

set_property(
    TEST Task1Test2
    PROPERTY PASS_REGULAR_EXPRESSION "1 2 3"
)


add_test(NAME Task2Test1
    COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/task2test1.txt
)

set_property(
    TEST Task2Test1
    PROPERTY PASS_REGULAR_EXPRESSION "1 4 0 0"
)


add_test(NAME Task2Test2
    COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/task2test2.txt
)

set_property(
    TEST Task2Test2
    PROPERTY PASS_REGULAR_EXPRESSION "5 25 0 0 0"
)
