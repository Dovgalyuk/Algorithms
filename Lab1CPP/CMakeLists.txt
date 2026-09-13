cmake_minimum_required(VERSION 3.10)

add_executable(task1 task1.cpp general.cpp)
target_include_directories(task1 PUBLIC ../LibraryCPP)
target_link_libraries(task1 LibraryCPP)

add_executable(task2 task2.cpp general.cpp)
target_include_directories(task2 PUBLIC ../LibraryCPP)
target_link_libraries(task2 LibraryCPP)

# Task 1 tests
# 1. Обычный случай
add_test(NAME Task1_Case1_Normal
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/input1.txt)
set_property(TEST Task1_Case1_Normal PROPERTY PASS_REGULAR_EXPRESSION "1 3")

# 2. Отрицательные числа
add_test(NAME Task1_Case2_Negative
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/input2.txt)
set_property(TEST Task1_Case2_Negative PROPERTY PASS_REGULAR_EXPRESSION "2 4")

# 3. Граница: все элементы равны -> пустой результат
add_test(NAME Task1_Case3_AllEqual
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/input3.txt)
set_property(TEST Task1_Case3_AllEqual PROPERTY PASS_REGULAR_EXPRESSION "")

# 4. Граница: массив из одного элемента
add_test(NAME Task1_Case4_SingleElement
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/input4.txt)
set_property(TEST Task1_Case4_SingleElement PROPERTY PASS_REGULAR_EXPRESSION "")

# 5. Граница: элемент точно равен среднему (строгое < должно его исключить)
add_test(NAME Task1_Case5_ExactAverage
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/input5.txt)
set_property(TEST Task1_Case5_ExactAverage PROPERTY PASS_REGULAR_EXPRESSION "0")

# 6. Исключение: несуществующий файл
add_test(NAME Task1_Case6_FileNotFound
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/does_not_exist.txt)
set_tests_properties(Task1_Case6_FileNotFound PROPERTIES PASS_REGULAR_EXPRESSION "Error opening file")

# 7. Исключение: не передан аргумент
add_test(NAME Task1_Case7_MissingArgument COMMAND task1)
set_tests_properties(Task1_Case7_MissingArgument PROPERTIES PASS_REGULAR_EXPRESSION "Usage:")


# Task 2 tests
# 1. Обычный случай: простые числа, никто ни на кого не делится
add_test(NAME Task2_Case1_Normal
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input1.txt)
set_property(TEST Task2_Case1_Normal PROPERTY PASS_REGULAR_EXPRESSION "2 3 5 7 11")

# 2. Есть единица + дубликаты -> все делятся, пусто
add_test(NAME Task2_Case2_WithOneAndDuplicates
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input2.txt)
set_property(TEST Task2_Case2_WithOneAndDuplicates PROPERTY PASS_REGULAR_EXPRESSION "")

# 3. Есть ноль -> защита от деления на 0, не должно упасть
add_test(NAME Task2_Case3_WithZero
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input3.txt)
set_property(TEST Task2_Case3_WithZero PROPERTY PASS_REGULAR_EXPRESSION "3")

# 4. Отрицательные числа
add_test(NAME Task2_Case4_Negative
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input4.txt)
set_property(TEST Task2_Case4_Negative PROPERTY PASS_REGULAR_EXPRESSION "2 3")

# 5. Граница: один элемент -> делить не на что, элемент остаётся
add_test(NAME Task2_Case5_SingleElement
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input5.txt)
set_property(TEST Task2_Case5_SingleElement PROPERTY PASS_REGULAR_EXPRESSION "7")

# 6. Граница: цепочка делителей, выживает только один элемент
add_test(NAME Task2_Case6_ChainDivisors
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input6.txt)
set_property(TEST Task2_Case6_ChainDivisors PROPERTY PASS_REGULAR_EXPRESSION "2")

# 7. Исключение: несуществующий файл
add_test(NAME Task2_Case7_FileNotFound
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/does_not_exist.txt)
set_tests_properties(Task2_Case7_FileNotFound PROPERTIES PASS_REGULAR_EXPRESSION "Error opening file")