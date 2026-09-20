add_executable(Lab1CPPTask1 task1.cpp)
add_executable(Lab1CPPTask2 task2.cpp)

target_include_directories(Lab1CPPTask1 PUBLIC ../LibraryCPPClass)
target_include_directories(Lab1CPPTask2 PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPPTask1 LibraryCPPClass)
target_link_libraries(Lab1CPPTask2 LibraryCPPClass)

# --- Task 1 (подсчёт смены знака) ---
add_test(NAME Task1_Test1 COMMAND Lab1CPPTask1 "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test1.txt")
set_property(TEST Task1_Test1 PROPERTY PASS_REGULAR_EXPRESSION "3")

add_test(NAME Task1_Test2 COMMAND Lab1CPPTask1 "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test2.txt")
set_property(TEST Task1_Test2 PROPERTY PASS_REGULAR_EXPRESSION "8")

add_test(NAME Task1_Test3 COMMAND Lab1CPPTask1 "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test3.txt")
set_property(TEST Task1_Test3 PROPERTY PASS_REGULAR_EXPRESSION "2")

add_test(NAME Task1_Test4 COMMAND Lab1CPPTask1 "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test4.txt")
set_property(TEST Task1_Test4 PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME Task1_Test5 COMMAND Lab1CPPTask1 "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test5.txt")
set_property(TEST Task1_Test5 PROPERTY PASS_REGULAR_EXPRESSION "5")

add_test(NAME Task1_Test6 COMMAND Lab1CPPTask1 "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_test6.txt")
set_property(TEST Task1_Test6 PROPERTY PASS_REGULAR_EXPRESSION "2")

# --- Task 2 (неделящиеся элементы) ---
add_test(NAME Task2_Test1 COMMAND Lab1CPPTask2 "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test1.txt")
set_property(TEST Task2_Test1 PROPERTY PASS_REGULAR_EXPRESSION "2 3 5 7 11")

add_test(NAME Task2_Test2 COMMAND Lab1CPPTask2 "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test2.txt")
set_property(TEST Task2_Test2 PROPERTY PASS_REGULAR_EXPRESSION "3 28 10")

add_test(NAME Task2_Test3 COMMAND Lab1CPPTask2 "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test3.txt")
set_property(TEST Task2_Test3 PROPERTY PASS_REGULAR_EXPRESSION "11 15 7 23 2")

add_test(NAME Task2_Test4 COMMAND Lab1CPPTask2 "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test4.txt")
set_property(TEST Task2_Test4 PROPERTY PASS_REGULAR_EXPRESSION "17 19 23 29 31 37 41 43 47 53 59 61 67 71 73")

add_test(NAME Task2_Test5 COMMAND Lab1CPPTask2 "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test5.txt")
set_property(TEST Task2_Test5 PROPERTY PASS_REGULAR_EXPRESSION "5")

add_test(NAME Task2_Test6 COMMAND Lab1CPPTask2 "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_test6.txt")
set_property(TEST Task2_Test6 PROPERTY PASS_REGULAR_EXPRESSION "7 11 13")