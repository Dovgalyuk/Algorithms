cmake_minimum_required(VERSION 3.15)

project(lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()


# ============================================================
# Программы
# ============================================================

add_executable(task1
    task1.cpp
    array.cpp
    array.h
)

add_executable(task2
    task2.cpp
    array.cpp
    array.h
)


# ============================================================
# Тесты task1
# ============================================================

add_test(
    NAME Task1Test1
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_input1.txt
)
set_tests_properties(Task1Test1 PROPERTIES
    PASS_REGULAR_EXPRESSION
    "2 3 5 7 0 0 0 0 0 0"
)

add_test(
    NAME Task1Test2
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_input2.txt
)
set_tests_properties(Task1Test2 PROPERTIES
    PASS_REGULAR_EXPRESSION
    "2 3 5 7 11 13 17 19 0 0 0 0 0 0 0 0 0 0 0 0"
)


# ============================================================
# Тесты task2
# ============================================================

add_test(
    NAME Task2Test1
    COMMAND task2
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_input1.txt
)
set_tests_properties(Task2Test1 PROPERTIES
    PASS_REGULAR_EXPRESSION "^2[ \t\r\n]*$"
)

add_test(
    NAME Task2Test2
    COMMAND task2
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_input2.txt
)
set_tests_properties(Task2Test2 PROPERTIES
    PASS_REGULAR_EXPRESSION "^2[ \t\r\n]*$"
)

add_test(
    NAME Task2Test3
    COMMAND task2
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_input3.txt
)
set_tests_properties(Task2Test3 PROPERTIES
    PASS_REGULAR_EXPRESSION "^6[ \t\r\n]*$"
)


# ============================================================
# Автоматический запуск тестов после сборки
# ============================================================

add_custom_target(run_tests ALL
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS task1 task2
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running all tests..."
)