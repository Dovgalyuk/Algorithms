add_executable(Lab1CPP main.cpp)

target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME Test1Lab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input1.txt)
set_property(TEST Test1Lab1CPP PROPERTY PASS_REGULAR_EXPRESSION "Среднее количество осадков: 3.875")

add_test(NAME Test2Lab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input1.txt)
set_property(TEST Test2Lab1CPP PROPERTY PASS_REGULAR_EXPRESSION "Максимальная сумма пяти соседних элементов: 40")

add_test(NAME Test3Lab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input2.txt)
set_property(TEST Test3Lab1CPP PROPERTY PASS_REGULAR_EXPRESSION "Дождливых дней не было.")

add_test(NAME Test4Lab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input2.txt)
set_property(TEST Test4Lab1CPP PROPERTY PASS_REGULAR_EXPRESSION "Массив меньше пяти элементов.")

add_test(NAME Test5Lab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input3.txt)
set_property(TEST Test5Lab1CPP PROPERTY PASS_REGULAR_EXPRESSION "Среднее количество осадков: 10")

add_test(NAME Test6Lab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input3.txt)
set_property(TEST Test6Lab1CPP PROPERTY PASS_REGULAR_EXPRESSION "Максимальная сумма пяти соседних элементов: -15")
