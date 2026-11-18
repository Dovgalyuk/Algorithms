add_executable(Lab3CPPRadix radix.cpp)
target_include_directories(Lab3CPPRadix PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab3CPPRadix LibraryCPPClass)

# Пример из описания задания
add_test(NAME TestLab3CPPRadix1 COMMAND Lab3CPPRadix ${CMAKE_CURRENT_SOURCE_DIR}/radix1.txt)
set_property(TEST TestLab3CPPRadix1 PROPERTY PASS_REGULAR_EXPRESSION "1 4 5 6 8")

# Многозначные числа: нужно несколько проходов
add_test(NAME TestLab3CPPRadix2 COMMAND Lab3CPPRadix ${CMAKE_CURRENT_SOURCE_DIR}/radix2.txt)
set_property(TEST TestLab3CPPRadix2 PROPERTY PASS_REGULAR_EXPRESSION "2 24 45 66 75 90 170 802")

# Повторяющиеся и большие числа
add_test(NAME TestLab3CPPRadix3 COMMAND Lab3CPPRadix ${CMAKE_CURRENT_SOURCE_DIR}/radix3.txt)
set_property(TEST TestLab3CPPRadix3 PROPERTY PASS_REGULAR_EXPRESSION "1 3 3 7 7 42 1000000 1000000")

# Отрицательное число: программа обязана завершиться с ошибкой
add_test(NAME TestLab3CPPRadixBad COMMAND Lab3CPPRadix ${CMAKE_CURRENT_SOURCE_DIR}/radix_bad.txt)
set_property(TEST TestLab3CPPRadixBad PROPERTY WILL_FAIL TRUE)