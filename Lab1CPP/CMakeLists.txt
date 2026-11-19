add_executable(task1 task1.cpp)
target_include_directories(task1 PRIVATE ../LibraryCPP)
target_link_libraries(task1 PRIVATE LibraryCPP)

add_executable(task2 task2.cpp)
target_include_directories(task2 PRIVATE ../LibraryCPP)
target_link_libraries(task2 PRIVATE LibraryCPP)

enable_testing()

# Тесты для task1
add_test(
    NAME test1_1
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
)

set_property(
    TEST test1_1
    PROPERTY PASS_REGULAR_EXPRESSION
    "5 4 3 2 1"
)

add_test(
    NAME test1_2
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/input1_2.txt
)

set_property(
    TEST test1_2
    PROPERTY PASS_REGULAR_EXPRESSION
    "40 30 20 10"
)

# Тесты для task2
add_test(
    NAME test2_1
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
)

set_property(
    TEST test2_1
    PROPERTY PASS_REGULAR_EXPRESSION
    "5"
)

add_test(
    NAME test2_2
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/input2_2.txt
)

set_property(
    TEST test2_2
    PROPERTY PASS_REGULAR_EXPRESSION
    "3 7"
)
