# Программа 1: индексы чётных элементов
add_executable(Lab1Task1CPP lab1task1.cpp)
target_include_directories(Lab1Task1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1Task1CPP LibraryCPP)

# Программа 2: элементы, встречающиеся ровно два раза
add_executable(Lab1Task2CPP lab1task2.cpp)
target_include_directories(Lab1Task2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1Task2CPP LibraryCPP)

# --- Тесты для программы 1 ---

# Тест 1.1: массив [1 2 3 4 5 6], чётные: 2(индекс 1), 4(индекс 3), 6(индекс 5)
add_test(NAME TestTask1_1 COMMAND Lab1Task1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1_1.txt)
set_property(TEST TestTask1_1 PROPERTY PASS_REGULAR_EXPRESSION "1 3 5")

# Тест 1.2: массив [1 3 5 7 9], все нечётные, результат — пустая строка
add_test(NAME TestTask1_2 COMMAND Lab1Task1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1_2.txt)
set_property(TEST TestTask1_2 PROPERTY FAIL_REGULAR_EXPRESSION "[0-9]")

# Тест 1.3: массив [2 4 6 8], все чётные, индексы: 0 1 2 3
add_test(NAME TestTask1_3 COMMAND Lab1Task1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1_3.txt)
set_property(TEST TestTask1_3 PROPERTY PASS_REGULAR_EXPRESSION "0 1 2 3")

# --- Тесты для программы 2 ---

# Тест 2.1: массив [1 2 3 2 5 3 7 1], ровно два раза встречаются: 1, 2, 3
add_test(NAME TestTask2_1 COMMAND Lab1Task2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2_1.txt)
set_property(TEST TestTask2_1 PROPERTY PASS_REGULAR_EXPRESSION "1 2 3")

# Тест 2.2: массив [10 20 30 40 50], все уникальны, результат — пустая строка
add_test(NAME TestTask2_2 COMMAND Lab1Task2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2_2.txt)
set_property(TEST TestTask2_2 PROPERTY FAIL_REGULAR_EXPRESSION "[0-9]")

# Тест 2.3: массив [5 5 100 100 100 0 0 999 999], ровно два раза: 0, 5, 999
add_test(NAME TestTask2_3 COMMAND Lab1Task2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2_3.txt)
set_property(TEST TestTask2_3 PROPERTY PASS_REGULAR_EXPRESSION "0 5 999")
