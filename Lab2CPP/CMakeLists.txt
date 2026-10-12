add_executable(Lab2CPPFish fish.cpp)
target_include_directories(Lab2CPPFish PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPPFish LibraryCPPClass)

# Пример из описания задания
add_test(NAME TestLab2CPPHello COMMAND Lab2CPPFish ${CMAKE_CURRENT_SOURCE_DIR}/hello.fish)
set_property(TEST TestLab2CPPHello PROPERTY PASS_REGULAR_EXPRESSION "Hello, world!")

# Арифметика и вывод числа: 5 * 6 - 1
add_test(NAME TestLab2CPPMath COMMAND Lab2CPPFish ${CMAKE_CURRENT_SOURCE_DIR}/math.fish)
set_property(TEST TestLab2CPPMath PROPERTY PASS_REGULAR_EXPRESSION "29")

# Цикл с условным переходом: обратный отсчёт
add_test(NAME TestLab2CPPCountdown COMMAND Lab2CPPFish ${CMAKE_CURRENT_SOURCE_DIR}/countdown.fish)
set_property(TEST TestLab2CPPCountdown PROPERTY PASS_REGULAR_EXPRESSION "54321")

# Чтение входных данных: скрипт копирует их на экран
add_test(NAME TestLab2CPPCat COMMAND Lab2CPPFish
         ${CMAKE_CURRENT_SOURCE_DIR}/cat.fish ${CMAKE_CURRENT_SOURCE_DIR}/cat_input.txt)
set_property(TEST TestLab2CPPCat PROPERTY PASS_REGULAR_EXPRESSION "Fish is swimming")

# Разворот строки: показывает работу стека, данные выводятся в обратном порядке
add_test(NAME TestLab2CPPReverse COMMAND Lab2CPPFish
         ${CMAKE_CURRENT_SOURCE_DIR}/reverse.fish ${CMAKE_CURRENT_SOURCE_DIR}/reverse_input.txt)
set_property(TEST TestLab2CPPReverse PROPERTY PASS_REGULAR_EXPRESSION "edcba")

# Неизвестная инструкция: программа обязана завершиться с ошибкой
add_test(NAME TestLab2CPPBad COMMAND Lab2CPPFish ${CMAKE_CURRENT_SOURCE_DIR}/bad.fish)
set_property(TEST TestLab2CPPBad PROPERTY WILL_FAIL TRUE)

# Зацикленный скрипт не должен останавливать сборку навсегда
set_tests_properties(TestLab2CPPHello TestLab2CPPMath TestLab2CPPCountdown
                     TestLab2CPPCat TestLab2CPPReverse TestLab2CPPBad
                     PROPERTIES TIMEOUT 10)