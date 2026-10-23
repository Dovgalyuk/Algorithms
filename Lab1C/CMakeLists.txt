add_executable(Lab1C_task1 task1.c)
target_include_directories(Lab1C_task1 PUBLIC ../LibraryC)
target_link_libraries(Lab1C_task1 LibraryC)

add_executable(Lab1C_task2 task2.c)
target_include_directories(Lab1C_task2 PUBLIC ../LibraryC)
target_link_libraries(Lab1C_task2 LibraryC)

# ============ Тесты для задачи 1 ============
add_test(NAME TestTask1_basic
         COMMAND Lab1C_task1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_basic.txt)
set_property(TEST TestTask1_basic PROPERTY
             PASS_REGULAR_EXPRESSION "Положительные числа: 1 2 3 4 5 6 7 8 9 ")

add_test(NAME TestTask1_mixed
         COMMAND Lab1C_task1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_mixed.txt)
set_property(TEST TestTask1_mixed PROPERTY
             PASS_REGULAR_EXPRESSION "Положительные числа: 1 3 5 7 9 ")

add_test(NAME TestTask1_all_negative
         COMMAND Lab1C_task1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_all_negative.txt)
set_property(TEST TestTask1_all_negative PROPERTY
             PASS_REGULAR_EXPRESSION "Отрицательные числа: -1 -2 -3 -4 -5 ")

add_test(NAME TestTask1_zeros_only
         COMMAND Lab1C_task1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_zeros_only.txt)
set_property(TEST TestTask1_zeros_only PROPERTY
             PASS_REGULAR_EXPRESSION "Положительные числа: \nОтрицательные числа: \n")

add_test(NAME TestTask1_single
         COMMAND Lab1C_task1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_single.txt)
set_property(TEST TestTask1_single PROPERTY
             PASS_REGULAR_EXPRESSION "Положительные числа: 42 ")

# ============ Тесты для задачи 2 ============
add_test(NAME TestTask2_basic
         COMMAND Lab1C_task2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_basic.txt)
set_property(TEST TestTask2_basic PROPERTY
             PASS_REGULAR_EXPRESSION "не делятся ни на какой другой элемент: 1 ")

add_test(NAME TestTask2_primes
         COMMAND Lab1C_task2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_primes.txt)
set_property(TEST TestTask2_primes PROPERTY
             PASS_REGULAR_EXPRESSION "не делятся ни на какой другой элемент: 3 7 11 13 17 19 ")

add_test(NAME TestTask2_divisible_chain
         COMMAND Lab1C_task2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_divisible_chain.txt)
set_property(TEST TestTask2_divisible_chain PROPERTY
             PASS_REGULAR_EXPRESSION "не делятся ни на какой другой элемент: 1 ")

add_test(NAME TestTask2_with_zero
         COMMAND Lab1C_task2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_with_zero.txt)
set_property(TEST TestTask2_with_zero PROPERTY
             PASS_REGULAR_EXPRESSION "не делятся ни на какой другой элемент: 2 3 5 ")

add_test(NAME TestTask2_duplicates
         COMMAND Lab1C_task2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_duplicates.txt)
set_property(TEST TestTask2_duplicates PROPERTY
             PASS_REGULAR_EXPRESSION "Таких элементов нет")

add_test(NAME TestTask2_single
         COMMAND Lab1C_task2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_single.txt)
set_property(TEST TestTask2_single PROPERTY
             PASS_REGULAR_EXPRESSION "не делятся ни на какой другой элемент: 7 ")