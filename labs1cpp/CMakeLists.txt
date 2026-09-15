add_executable(Lab1CPPTask1 task1.cpp)
add_executable(Lab1CPPTask2 task2.cpp)

target_include_directories(Lab1CPPTask1 PUBLIC ../LibraryCPPTemplate)
target_include_directories(Lab1CPPTask2 PUBLIC ../LibraryCPPTemplate)


file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tests")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test1.txt"
    "5\n5 -2 0 8 -4\n1 2\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test2.txt"
    "3\n2 4 6\n1 3\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test3.txt"
    "3\n-2 0 -6\n1 3\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test4.txt"
    "1\n5\n1 1\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test5.txt"
    "3\n0 0 0\n1 2\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test6.txt"
    "3\n2 4 6\n3 1\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test7.txt"
    "3\n-2 -4 -6\n3 1\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test8.txt"
    "4\n3 -5 0 7\n1 1\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test9.txt"
    "4\n5 -2 0 8\n2 2\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test10.txt"
    "4\n-5 10 -2 0\n2 1\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test1.txt"
    "5\n2 8 5 12 7\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test2.txt"
    "4\n-8 -2 4 9\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test3.txt"
    "4\n2 2 6 9\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test4.txt"
    "3\n4 4 4\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test5.txt"
    "3\n0 6 9\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test6.txt"
    "3\n1 3 5\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test7.txt"
    "1\n8\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test8.txt"
    "4\n10 4 8 3\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test9.txt"
    "2\n-4 6\n")

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test10.txt"
    "2\n-2147483648 2147483646\n")

add_test(NAME Task1_Test1 COMMAND Lab1CPPTask1
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test1.txt")
set_property(TEST Task1_Test1 PROPERTY
    PASS_REGULAR_EXPRESSION "^0 0 2 3 -2[\r\n]*$")

add_test(NAME Task1_Test2 COMMAND Lab1CPPTask1
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test2.txt")
set_property(TEST Task1_Test2 PROPERTY
    PASS_REGULAR_EXPRESSION "^0 2 4[\r\n]*$")

add_test(NAME Task1_Test3 COMMAND Lab1CPPTask1
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test3.txt")
set_property(TEST Task1_Test3 PROPERTY
    PASS_REGULAR_EXPRESSION "^4 6 0[\r\n]*$")

add_test(NAME Task1_Test4 COMMAND Lab1CPPTask1
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test4.txt")
set_property(TEST Task1_Test4 PROPERTY
    PASS_REGULAR_EXPRESSION "^0[\r\n]*$")

add_test(NAME Task1_Test5 COMMAND Lab1CPPTask1
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test5.txt")
set_property(TEST Task1_Test5 PROPERTY
    PASS_REGULAR_EXPRESSION "^0 0 0[\r\n]*$")

add_test(NAME Task1_Test6 COMMAND Lab1CPPTask1
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test6.txt")
set_property(TEST Task1_Test6 PROPERTY
    PASS_REGULAR_EXPRESSION "^-4 -2 0[\r\n]*$")

add_test(NAME Task1_Test7 COMMAND Lab1CPPTask1
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test7.txt")
set_property(TEST Task1_Test7 PROPERTY
    PASS_REGULAR_EXPRESSION "^0 -2 -4[\r\n]*$")

add_test(NAME Task1_Test8 COMMAND Lab1CPPTask1
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test8.txt")
set_property(TEST Task1_Test8 PROPERTY
    PASS_REGULAR_EXPRESSION "^0 -8 -3 4[\r\n]*$")

add_test(NAME Task1_Test9 COMMAND Lab1CPPTask1
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test9.txt")
set_property(TEST Task1_Test9 PROPERTY
    PASS_REGULAR_EXPRESSION "^7 0 2 10[\r\n]*$")

add_test(NAME Task1_Test10 COMMAND Lab1CPPTask1
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test10.txt")
set_property(TEST Task1_Test10 PROPERTY
    PASS_REGULAR_EXPRESSION "^0 0 3 5[\r\n]*$")

add_test(NAME Task2_Test1 COMMAND Lab1CPPTask2
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test1.txt")
set_property(TEST Task2_Test1 PROPERTY
    PASS_REGULAR_EXPRESSION "^4[\r\n]*$")

add_test(NAME Task2_Test2 COMMAND Lab1CPPTask2
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test2.txt")
set_property(TEST Task2_Test2 PROPERTY
    PASS_REGULAR_EXPRESSION "^6[\r\n]*$")

add_test(NAME Task2_Test3 COMMAND Lab1CPPTask2
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test3.txt")
set_property(TEST Task2_Test3 PROPERTY
    PASS_REGULAR_EXPRESSION "^4[\r\n]*$")

add_test(NAME Task2_Test4 COMMAND Lab1CPPTask2
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test4.txt")
set_property(TEST Task2_Test4 PROPERTY
    PASS_REGULAR_EXPRESSION "^Нет пары разных четных значений[\r\n]*$")

add_test(NAME Task2_Test5 COMMAND Lab1CPPTask2
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test5.txt")
set_property(TEST Task2_Test5 PROPERTY
    PASS_REGULAR_EXPRESSION "^6[\r\n]*$")

add_test(NAME Task2_Test6 COMMAND Lab1CPPTask2
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test6.txt")
set_property(TEST Task2_Test6 PROPERTY
    PASS_REGULAR_EXPRESSION "^Нет пары разных четных значений[\r\n]*$")

add_test(NAME Task2_Test7 COMMAND Lab1CPPTask2
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test7.txt")
set_property(TEST Task2_Test7 PROPERTY
    PASS_REGULAR_EXPRESSION "^Нет пары разных четных значений[\r\n]*$")

add_test(NAME Task2_Test8 COMMAND Lab1CPPTask2
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test8.txt")
set_property(TEST Task2_Test8 PROPERTY
    PASS_REGULAR_EXPRESSION "^2[\r\n]*$")

add_test(NAME Task2_Test9 COMMAND Lab1CPPTask2
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test9.txt")
set_property(TEST Task2_Test9 PROPERTY
    PASS_REGULAR_EXPRESSION "^10[\r\n]*$")

add_test(NAME Task2_Test10 COMMAND Lab1CPPTask2
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test10.txt")
set_property(TEST Task2_Test10 PROPERTY
    PASS_REGULAR_EXPRESSION "^4294967294[\r\n]*$")