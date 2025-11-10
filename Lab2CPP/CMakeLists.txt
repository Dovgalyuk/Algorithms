cmake_minimum_required(VERSION 3.10)
project(Lab2CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab2CPP main.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

enable_testing()

add_test(NAME TestLab2CPPFile1 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(TestLab2CPPFile1 PROPERTIES PASS_REGULAR_EXPRESSION "3.*2.*1")

add_test(NAME TestLab2CPPFile2 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(TestLab2CPPFile2 PROPERTIES PASS_REGULAR_EXPRESSION "1.*2.*3.*6")

add_test(NAME TestLab2CPPFile3 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_tests_properties(TestLab2CPPFile3 PROPERTIES PASS_REGULAR_EXPRESSION "5")

# Тест 1: Базовый вывод чисел - используем более гибкое регулярное выражение
add_test(NAME TestLab2CPP1 COMMAND Lab2CPP "123...")
set_tests_properties(TestLab2CPP1 PROPERTIES PASS_REGULAR_EXPRESSION "3.*2.*1")

# Тест 2: Арифметические операции - используем более гибкое регулярное выражение
add_test(NAME TestLab2CPP2 COMMAND Lab2CPP "1:.2:.3:.++.")
set_tests_properties(TestLab2CPP2 PROPERTIES PASS_REGULAR_EXPRESSION "1.*2.*3.*6")

# Тест 3: Сложение
add_test(NAME TestLab2CPP3 COMMAND Lab2CPP "23+.")
set_tests_properties(TestLab2CPP3 PROPERTIES PASS_REGULAR_EXPRESSION "5")

# Тест 4: Умножение
add_test(NAME TestLab2CPP4 COMMAND Lab2CPP "23*.")
set_tests_properties(TestLab2CPP4 PROPERTIES PASS_REGULAR_EXPRESSION "6")

# Тест 5: Логическое НЕ
add_test(NAME TestLab2CPP5 COMMAND Lab2CPP "0!.")
set_tests_properties(TestLab2CPP5 PROPERTIES PASS_REGULAR_EXPRESSION "1")

# Тест 6: Сравнение
add_test(NAME TestLab2CPP6 COMMAND Lab2CPP "52`.")
set_tests_properties(TestLab2CPP6 PROPERTIES PASS_REGULAR_EXPRESSION "1")

# Тест 7: Дублирование - используем более гибкое регулярное выражение
add_test(NAME TestLab2CPP7 COMMAND Lab2CPP "5:..")
set_tests_properties(TestLab2CPP7 PROPERTIES PASS_REGULAR_EXPRESSION "5.*5")