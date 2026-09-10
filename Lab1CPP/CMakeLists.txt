add_executable(Lab1Task1 lab1_task1.cpp)
target_include_directories(Lab1Task1 PRIVATE ../LibraryCPP)
target_link_libraries(Lab1Task1 PRIVATE LibraryCPP)

add_executable(Lab1Task2 lab1_task2.cpp)
target_include_directories(Lab1Task2 PRIVATE ../LibraryCPP)
target_link_libraries(Lab1Task2 PRIVATE LibraryCPP)

# Тесты
add_test(
    NAME TestLab1Task11
    COMMAND Lab1Task1 ${CMAKE_CURRENT_SOURCE_DIR}/input1_task1.txt
)

set_property(
    TEST TestLab1Task11
    PROPERTY PASS_REGULAR_EXPRESSION
    "1 2 6 24 120"
)

add_test(
    NAME TestLab1Task12
    COMMAND Lab1Task1 ${CMAKE_CURRENT_SOURCE_DIR}/input2_task1.txt
)

set_property(
    TEST TestLab1Task12
    PROPERTY PASS_REGULAR_EXPRESSION
    "1 6 24"
)



add_test(
    NAME TestLab1Task21
    COMMAND Lab1Task2 ${CMAKE_CURRENT_SOURCE_DIR}/input1_task2.txt
)

set_property(
    TEST TestLab1Task21
    PROPERTY PASS_REGULAR_EXPRESSION
    "1 3 2 2 3 1"
)

add_test(
    NAME TestLab1Task22
    COMMAND Lab1Task2 ${CMAKE_CURRENT_SOURCE_DIR}/input2_task2.txt
)

set_property(
    TEST TestLab1Task22
    PROPERTY PASS_REGULAR_EXPRESSION
    "5 5"
)