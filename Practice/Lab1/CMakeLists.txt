cmake_minimum_required(VERSION 3.15)
project(MyArrayTask CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем библиотеку с шаблоном Array<T>.
# Путь ../../LibraryCPPTemplate = Algorithms/LibraryCPPTemplate
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../LibraryCPPTemplate
                 ${CMAKE_CURRENT_BINARY_DIR}/libcpptemplate)

add_executable(task1 task1.cpp)
add_executable(task2 task2.cpp)
target_link_libraries(task1 PRIVATE ArrayTemplate)
target_link_libraries(task2 PRIVATE ArrayTemplate)

enable_testing()

# ---------- Task 1 ----------
add_test(NAME task1_test1
    COMMAND task1
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/input1_1.txt
        ${CMAKE_CURRENT_BINARY_DIR}/out1_1.txt)
set_tests_properties(task1_test1 PROPERTIES FIXTURES_SETUP setup1_1)
add_test(NAME task1_check1
    COMMAND ${CMAKE_COMMAND}
        -DACTUAL=${CMAKE_CURRENT_BINARY_DIR}/out1_1.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/expected1_1.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/compare.cmake)
set_tests_properties(task1_check1 PROPERTIES FIXTURES_REQUIRED setup1_1)

add_test(NAME task1_test2
    COMMAND task1
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/input1_2.txt
        ${CMAKE_CURRENT_BINARY_DIR}/out1_2.txt)
set_tests_properties(task1_test2 PROPERTIES FIXTURES_SETUP setup1_2)
add_test(NAME task1_check2
    COMMAND ${CMAKE_COMMAND}
        -DACTUAL=${CMAKE_CURRENT_BINARY_DIR}/out1_2.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/expected1_2.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/compare.cmake)
set_tests_properties(task1_check2 PROPERTIES FIXTURES_REQUIRED setup1_2)

add_test(NAME task1_test3
    COMMAND task1
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/input1_3.txt
        ${CMAKE_CURRENT_BINARY_DIR}/out1_3.txt)
set_tests_properties(task1_test3 PROPERTIES FIXTURES_SETUP setup1_3)
add_test(NAME task1_check3
    COMMAND ${CMAKE_COMMAND}
        -DACTUAL=${CMAKE_CURRENT_BINARY_DIR}/out1_3.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/expected1_3.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/compare.cmake)
set_tests_properties(task1_check3 PROPERTIES FIXTURES_REQUIRED setup1_3)

# ---------- Task 2 ----------
add_test(NAME task2_test1
    COMMAND task2
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/input2_1.txt
        ${CMAKE_CURRENT_BINARY_DIR}/out2_1.txt)
set_tests_properties(task2_test1 PROPERTIES FIXTURES_SETUP setup2_1)
add_test(NAME task2_check1
    COMMAND ${CMAKE_COMMAND}
        -DACTUAL=${CMAKE_CURRENT_BINARY_DIR}/out2_1.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/expected2_1.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/compare.cmake)
set_tests_properties(task2_check1 PROPERTIES FIXTURES_REQUIRED setup2_1)

add_test(NAME task2_test2
    COMMAND task2
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/input2_2.txt
        ${CMAKE_CURRENT_BINARY_DIR}/out2_2.txt)
set_tests_properties(task2_test2 PROPERTIES FIXTURES_SETUP setup2_2)
add_test(NAME task2_check2
    COMMAND ${CMAKE_COMMAND}
        -DACTUAL=${CMAKE_CURRENT_BINARY_DIR}/out2_2.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/expected2_2.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/compare.cmake)
set_tests_properties(task2_check2 PROPERTIES FIXTURES_REQUIRED setup2_2)

add_test(NAME task2_test3
    COMMAND task2
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/input2_3.txt
        ${CMAKE_CURRENT_BINARY_DIR}/out2_3.txt)
set_tests_properties(task2_test3 PROPERTIES FIXTURES_SETUP setup2_3)
add_test(NAME task2_check3
    COMMAND ${CMAKE_COMMAND}
        -DACTUAL=${CMAKE_CURRENT_BINARY_DIR}/out2_3.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/expected2_3.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/compare.cmake)
set_tests_properties(task2_check3 PROPERTIES FIXTURES_REQUIRED setup2_3)