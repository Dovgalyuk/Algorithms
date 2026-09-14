add_executable(Lab1C_task1 lab1_task1.cpp)
add_executable(Lab1C_task2 lab1_task2.cpp)

# Подключаем заголовки библиотеки LibraryC
target_include_directories(Lab1C_task1 PUBLIC ../LibraryC)
target_include_directories(Lab1C_task2 PUBLIC ../LibraryC)

# Тест Задания 4 (task1)
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/input1.txt "5
1 4 3 6 8
")
add_test(NAME TestLab1C_Task1 COMMAND Lab1C_task1 ${CMAKE_CURRENT_BINARY_DIR}/input1.txt)
set_tests_properties(TestLab1C_Task1 PROPERTIES PASS_REGULAR_EXPRESSION "1 3 4")

# Тест Задания 5 (task2)
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/input2.txt "5
10 4 18 3 8
")
add_test(NAME TestLab1C_Task2 COMMAND Lab1C_task2 ${CMAKE_CURRENT_BINARY_DIR}/input2.txt)
set_tests_properties(TestLab1C_Task2 PROPERTIES PASS_REGULAR_EXPRESSION "2")