cmake_minimum_required(VERSION 3.15)
project(Lab1 CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Lab1 STATIC lab1.cpp)
target_include_directories(Lab1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Lab1 PUBLIC LibraryCPP)

add_executable(task1 task1.cpp)
target_link_libraries(task1 PRIVATE Lab1)

add_executable(task2 task2.cpp)
target_link_libraries(task2 PRIVATE Lab1)

enable_testing()

add_test(NAME Task1_Test1
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_1.txt) 
set_property(TEST Task1_Test1 PROPERTY PASS_REGULAR_EXPRESSION "2 3 5 7 0 0 0 0 0 0")

add_test(NAME Task1_Test2
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_2.txt) 
set_property(TEST Task1_Test2 PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME Task1_Test3
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_3.txt) 
set_property(TEST Task1_Test3 PROPERTY PASS_REGULAR_EXPRESSION "2 0")

add_test(NAME Task1_Test4
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_4.txt) 
set_property(TEST Task1_Test4 PROPERTY PASS_REGULAR_EXPRESSION "2 3 5 7 11 13 17 19 0 0 0 0 0 0 0 0 0 0 0 0")

add_test(NAME Task1_Test5
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_5.txt) 
set_property(TEST Task1_Test5 PROPERTY PASS_REGULAR_EXPRESSION "2 3 5 7 11 13 17 19 23 29 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0")

add_test(NAME Task1_Test6
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_6.txt) 
set_property(TEST Task1_Test6 PROPERTY PASS_REGULAR_EXPRESSION "Ошибка: некорректный размер массива")

add_test(NAME Task2_Test1
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_1.txt) 
set_property(TEST Task2_Test1 PROPERTY PASS_REGULAR_EXPRESSION "213213")

add_test(NAME Task2_Test2
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_2.txt) 
set_property(TEST Task2_Test2 PROPERTY PASS_REGULAR_EXPRESSION "55")

add_test(NAME Task2_Test3
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_3.txt) 
set_property(TEST Task2_Test3 PROPERTY PASS_REGULAR_EXPRESSION "11121315")

add_test(NAME Task2_Test4
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_4.txt) 
set_property(TEST Task2_Test4 PROPERTY PASS_REGULAR_EXPRESSION "115")

add_test(NAME Task2_Test5
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_5.txt) 
set_property(TEST Task2_Test5 PROPERTY PASS_REGULAR_EXPRESSION "3-1222-3")

add_test(NAME Task2_Test6
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_6.txt) 
set_property(TEST Task2_Test6 PROPERTY PASS_REGULAR_EXPRESSION "152")


add_custom_target(test_all
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS task1 task2  
    COMMENT "Running all tests..."
)