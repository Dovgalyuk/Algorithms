# Программа 1: подсчёт положительных, отрицательных и нулевых элементов
add_executable(Lab1CPPCount count.cpp)
target_include_directories(Lab1CPPCount PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPPCount LibraryCPPClass)

add_test(NAME TestLab1CPPCount1 COMMAND Lab1CPPCount ${CMAKE_CURRENT_SOURCE_DIR}/count1.txt)
set_property(TEST TestLab1CPPCount1 PROPERTY PASS_REGULAR_EXPRESSION "Positive: 4 Negative: 3 Zero: 3")

add_test(NAME TestLab1CPPCount2 COMMAND Lab1CPPCount ${CMAKE_CURRENT_SOURCE_DIR}/count2.txt)
set_property(TEST TestLab1CPPCount2 PROPERTY PASS_REGULAR_EXPRESSION "Positive: 0 Negative: 0 Zero: 5")

add_test(NAME TestLab1CPPCount3 COMMAND Lab1CPPCount ${CMAKE_CURRENT_SOURCE_DIR}/count3.txt)
set_property(TEST TestLab1CPPCount3 PROPERTY PASS_REGULAR_EXPRESSION "Positive: 0 Negative: 6 Zero: 0")

# Программа 2: поиск наиболее часто встречающегося значения за O(N)
add_executable(Lab1CPPFrequency frequency.cpp)
target_include_directories(Lab1CPPFrequency PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPPFrequency LibraryCPPClass)

add_test(NAME TestLab1CPPFrequency1 COMMAND Lab1CPPFrequency ${CMAKE_CURRENT_SOURCE_DIR}/freq1.txt)
set_property(TEST TestLab1CPPFrequency1 PROPERTY PASS_REGULAR_EXPRESSION "Most frequent value: 3, count: 4")

add_test(NAME TestLab1CPPFrequency2 COMMAND Lab1CPPFrequency ${CMAKE_CURRENT_SOURCE_DIR}/freq2.txt)
set_property(TEST TestLab1CPPFrequency2 PROPERTY PASS_REGULAR_EXPRESSION "Most frequent value: 5, count: 2")

add_test(NAME TestLab1CPPFrequency3 COMMAND Lab1CPPFrequency ${CMAKE_CURRENT_SOURCE_DIR}/freq3.txt)
set_property(TEST TestLab1CPPFrequency3 PROPERTY PASS_REGULAR_EXPRESSION "Most frequent value: 1000, count: 3")

# Некорректные данные: программа обязана завершиться с ошибкой
add_test(NAME TestLab1CPPFrequencyBad COMMAND Lab1CPPFrequency ${CMAKE_CURRENT_SOURCE_DIR}/freq_bad.txt)
set_property(TEST TestLab1CPPFrequencyBad PROPERTY WILL_FAIL TRUE)