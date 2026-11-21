add_executable(Task1CPP task1.cpp)
target_include_directories(Task1CPP PRIVATE ../LibraryCPP)
target_link_libraries(Task1CPP PRIVATE LibraryCPP)

add_executable(Task2CPP task2.cpp)
target_include_directories(Task2CPP PRIVATE ../LibraryCPP)
target_link_libraries(Task2CPP PRIVATE LibraryCPP)

# тесты дл€ задачи 1: ѕрочитать целое число из файла, создать массив такой размерности. «аполнить массив натуральными числами. 
# ¬ычеркнуть лишние, использу€ решето Ёратосфена. ќставшиес€ числа перенести в начало массива, пустое место заполнить нул€ми. ¬ывести массив на экран или в файл.
add_test(
    NAME TestTask1CPP_10
    COMMAND Task1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input_task1_10.txt
)

# массив размером 10, набор данных: 1 2 3 4 5 6 7 8 9 10
# остаютс€ простые числа 2 3 5 7, остальные 0 (вычеркиваютс€ числа кратные и 1)
set_property(
    TEST TestTask1CPP_10
    PROPERTY PASS_REGULAR_EXPRESSION
    "^2 3 5 7 0 0 0 0 0 0[\r\n]*$"
)

add_test(
    NAME TestTask1CPP_20
    COMMAND Task1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input_task1_20.txt
)

# массив размером 20, набор данных: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
# остаютс€ простые числа 2 3 5 7 11 13 17 19, остальные 0 (вычеркиваютс€ числа кратные и 1)
set_property(
    TEST TestTask1CPP_20
    PROPERTY PASS_REGULAR_EXPRESSION
    "^2 3 5 7 11 13 17 19 0 0 0 0 0 0 0 0 0 0 0 0[\r\n]*$"
)

# тесты дл€ задачи 2: ѕрочитать целое число из файла, создать массив такой размерности и заполнить его числами из файла. 
# Ќайти п€ть соседних элементов, сумма значений которых максимальна. ¬ывести результат на экран или в файл.
add_test(
    NAME TestTask2CPP_1
    COMMAND Task2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input_task2_1.txt
)

# размер матрицы: 5 набор данных: 1 2 3 4 5, максимальна€ сумма п€ти элементов - 15
set_property(
    TEST TestTask2CPP_1
    PROPERTY PASS_REGULAR_EXPRESSION
    "^15[\r\n]+1 2 3 4 5[\r\n]*$"
)

add_test(
    NAME TestTask2CPP_2
    COMMAND Task2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input_task2_2.txt
)

# размер матрицы :10 набор данных: 1 2 10 4 5 1 2 3 100 1, максимальна€ сумма п€ти соседних элементов - 111
set_property(
    TEST TestTask2CPP_2
    PROPERTY PASS_REGULAR_EXPRESSION
    "^111[\r\n]+5 1 2 3 100[\r\n]*$"
)