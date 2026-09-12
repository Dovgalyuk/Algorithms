cmake_minimum_required(VERSION 3.10)

project(Lab1CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task1 Task1.cpp general.cpp)

add_executable(task2 Task2.cpp general.cpp)

target_include_directories(task1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP)
target_link_libraries(task1 LibraryCPP)

target_include_directories(task2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP)
target_link_libraries(task2 LibraryCPP)

enable_testing()

add_test(NAME Task1_Test1
        COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_1
)
set_property(TEST Task1_Test1 PROPERTY PASS_REGULAR_EXPRESSION
        "Среднее арифметическое положительных:.*8"
)
add_test(NAME Task1_Test2
        COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_2
)
set_property(TEST Task1_Test2 PROPERTY PASS_REGULAR_EXPRESSION
        "Среднее арифметическое положительных:.*17"
)
add_test(NAME Task1_Test3
        COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_3
)
set_property(TEST Task1_Test3 PROPERTY PASS_REGULAR_EXPRESSION
        "Среднее арифметическое отрицательных:.*-20"
)
add_test(NAME Task1_Test4
        COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_4
)
set_property(TEST Task1_Test4 PROPERTY PASS_REGULAR_EXPRESSION
        "Среднее арифметическое положительных:.*9"
)
add_test(NAME Task1_Test5
        COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_5
)
set_property(TEST Task1_Test5 PROPERTY PASS_REGULAR_EXPRESSION
        "Среднее арифметическое положительных:.*88"
)
add_test(NAME Task1_Test6
        COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_6
)
set_property(TEST Task1_Test6 PROPERTY PASS_REGULAR_EXPRESSION
        "Среднее арифметическое положительных:.*550000"
)
add_test(NAME Task2_Test1
        COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_1
)
set_property(TEST Task2_Test1 PROPERTY PASS_REGULAR_EXPRESSION
        "3.*99|99.*3"
)
add_test(NAME Task2_Test2
        COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_2
)
set_property(TEST Task2_Test2 PROPERTY PASS_REGULAR_EXPRESSION
        "11.*22.*33.*44.*55"
)
add_test(NAME Task2_Test3
        COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_3
)
set_property(TEST Task2_Test3 PROPERTY PASS_REGULAR_EXPRESSION
        "Таких элементов нет"
)
add_test(NAME Task2_Test4
        COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_4
)
set_property(TEST Task2_Test4 PROPERTY PASS_REGULAR_EXPRESSION
        "Таких элементов нет"
)
add_test(NAME Task2_Test5
        COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_5
)
set_property(TEST Task2_Test5 PROPERTY PASS_REGULAR_EXPRESSION
        "1.*500.*999"
)
add_test(NAME Task2_Test6
        COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_6
)
set_property(TEST Task2_Test6 PROPERTY PASS_REGULAR_EXPRESSION
        "42"
)
add_custom_target(test_all
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS task1 task2
        COMMENT "Запуск всех тестов..."
)