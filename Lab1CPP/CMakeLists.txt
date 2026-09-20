add_executable(test_array test.cpp Array.h)
add_executable(task1 task1.cpp Array.h)
add_executable(task2 task2.cpp Array.h)

# 1. Тест базового контейнера
add_test(NAME CheckContainer COMMAND test_array)
set_tests_properties(CheckContainer PROPERTIES PASS_REGULAR_EXPRESSION "10 20 30 40 50")

# 2. Тест разворота массива (task1)
add_test(NAME CheckReverse COMMAND task1 "${CMAKE_CURRENT_SOURCE_DIR}/input1.txt")
set_tests_properties(CheckReverse PROPERTIES PASS_REGULAR_EXPRESSION "5 4 3 2 1")

# 3. Тест поиска элементов (task2)
add_test(NAME CheckTwoOccurrences COMMAND task2 "${CMAKE_CURRENT_SOURCE_DIR}/input2.txt")
set_tests_properties(CheckTwoOccurrences PROPERTIES PASS_REGULAR_EXPRESSION "5")
