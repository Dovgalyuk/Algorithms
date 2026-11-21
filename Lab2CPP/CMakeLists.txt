add_executable(Lab2CPP main.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

# Тест 1: Пример из задания (скрипт {]{{), вход CBA, вывод A \n B \n C)
add_test(NAME Lab2TestExample COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/example.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/example.in)
set_property(TEST Lab2TestExample PROPERTY PASS_REGULAR_EXPRESSION "^A\nB\nC\n$")

# Тест 2: Перемещение всех дисков на 3-й стержень
add_test(NAME Lab2TestMoveAll COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/move_all.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/move_all.in)
set_property(TEST Lab2TestMoveAll PROPERTY PASS_REGULAR_EXPRESSION "^\n\nCBA\n$")

# Тест 3: Распределение дисков между стержнями 2 и 3
add_test(NAME Lab2TestMoveBetween COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/move_between.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/move_between.in)
set_property(TEST Lab2TestMoveBetween PROPERTY PASS_REGULAR_EXPRESSION "^\nBA\nC\n$")

# Тест 4: Дублирование элемента на стержне 2 (команда >)
add_test(NAME Lab2TestDuplicate COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/duplicate.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/duplicate.in)
set_property(TEST Lab2TestDuplicate PROPERTY PASS_REGULAR_EXPRESSION "^\naa\n\n$")

# Тест 5: Дедупликация равных элементов (команда <)
add_test(NAME Lab2TestDeduplicate COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/deduplicate.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/deduplicate.in)
set_property(TEST Lab2TestDeduplicate PROPERTY PASS_REGULAR_EXPRESSION "^\na\n\n$")

# Тест 6: Вывод символа через команду }
add_test(NAME Lab2TestCat COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/cat.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/cat.in)
set_property(TEST Lab2TestCat PROPERTY PASS_REGULAR_EXPRESSION "^H\n\n\n\n$")

# Тест 7: Вычитание (команда -)
add_test(NAME Lab2TestSubtract COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/subtract.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/subtract.in)
set_property(TEST Lab2TestSubtract PROPERTY PASS_REGULAR_EXPRESSION "^\nd\\\\x01\n\n$")

# Тест 8: Игнорирование комментариев и пробелов в скрипте
add_test(NAME Lab2TestComments COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/comments.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/comments.in)
set_property(TEST Lab2TestComments PROPERTY PASS_REGULAR_EXPRESSION "^A\nB\nC\n$")

# Тест 9: Ошибка нарушения правила Ханойских башен (больший диск на меньший)
add_test(NAME Lab2TestErrorRule COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/error_rule.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/error_rule.in)
set_property(TEST Lab2TestErrorRule PROPERTY PASS_REGULAR_EXPRESSION "rule violated")

# Тест 10: Ошибка дедупликации неравных элементов
add_test(NAME Lab2TestErrorIrreversible COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/error_irreversible.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/error_irreversible.in)
set_property(TEST Lab2TestErrorIrreversible PROPERTY PASS_REGULAR_EXPRESSION "irreversible")

# Тест 11: Пустой скрипт и пустой ввод
add_test(NAME Lab2TestEmpty COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/empty.hanoi ${CMAKE_CURRENT_SOURCE_DIR}/Tests/empty.in)
set_property(TEST Lab2TestEmpty PROPERTY PASS_REGULAR_EXPRESSION "^\n\n\n$")
