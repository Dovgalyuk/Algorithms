add_executable(ConsoleApplication2 ConsoleApplication2.cpp)

add_test(NAME TestConsoleApp1 COMMAND ConsoleApplication2 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestConsoleApp1 PROPERTY PASS_REGULAR_EXPRESSION "Массив палиндромов: 0 1 2 3 4 5 6 7 8 9")

add_test(NAME TestConsoleApp2 COMMAND ConsoleApplication2 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestConsoleApp2 PROPERTY PASS_REGULAR_EXPRESSION "Минимальная разность четных элементов: 2")
