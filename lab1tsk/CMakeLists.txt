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

#testi1

add_test(
    NAME Task1_Test1
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1_1.txt
            ${CMAKE_CURRENT_BINARY_DIR}/task1_1_output.txt
)
add_test(
    NAME Task1_Check1
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/task1_1_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1_1_expected.txt
)
set_tests_properties(
    Task1_Check1
    PROPERTIES DEPENDS Task1_Test1
)

add_test(
    NAME Task1_Test2
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1_2.txt
            ${CMAKE_CURRENT_BINARY_DIR}/task1_2_output.txt
)
add_test(
    NAME Task1_Check2
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/task1_2_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1_2_expected.txt
)
set_tests_properties(
    Task1_Check2
    PROPERTIES DEPENDS Task1_Test2
)

add_test(
    NAME Task1_Test3
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1_3.txt
            ${CMAKE_CURRENT_BINARY_DIR}/task1_3_output.txt
)

add_test(
    NAME Task1_Check3
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/task1_3_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1_3_expected.txt
)
set_tests_properties(
    Task1_Check3
    PROPERTIES DEPENDS Task1_Test3
)

add_test(
    NAME Task1_Test4
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1_4.txt
            ${CMAKE_CURRENT_BINARY_DIR}/task1_4_output.txt
)
add_test(
    NAME Task1_Check4
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/task1_4_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1_4_expected.txt
)
set_tests_properties(
    Task1_Check4
    PROPERTIES DEPENDS Task1_Test4
)

add_test(
    NAME Task1_Test5
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1_5.txt
            ${CMAKE_CURRENT_BINARY_DIR}/task1_5_output.txt
)
add_test(
    NAME Task1_Check5
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/task1_5_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1_5_expected.txt
)
set_tests_properties(
    Task1_Check5
    PROPERTIES DEPENDS Task1_Test5
)

add_test(
    NAME Task1_Test6
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1_6.txt
            ${CMAKE_CURRENT_BINARY_DIR}/task1_6_output.txt
)
add_test(
    NAME Task1_Check6
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/task1_6_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1_6_expected.txt
)
set_tests_properties(
    Task1_Check6
    PROPERTIES DEPENDS Task1_Test6
)

#2

add_test(
    NAME Task2_Test1
    COMMAND task2
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2_1.txt
            ${CMAKE_CURRENT_BINARY_DIR}/task2_1_output.txt
)
add_test(
    NAME Task2_Check1
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/task2_1_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2_1_expected.txt
)
set_tests_properties(
    Task2_Check1
    PROPERTIES DEPENDS Task2_Test1
)

add_test(
    NAME Task2_Test2
    COMMAND task2
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2_2.txt
            ${CMAKE_CURRENT_BINARY_DIR}/task2_2_output.txt
)
add_test(
    NAME Task2_Check2
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/task2_2_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2_2_expected.txt
)
set_tests_properties(
    Task2_Check2
    PROPERTIES DEPENDS Task2_Test2
)

add_test(
    NAME Task2_Test3
    COMMAND task2
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2_3.txt
            ${CMAKE_CURRENT_BINARY_DIR}/task2_3_output.txt
)
add_test(
    NAME Task2_Check3
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/task2_3_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2_3_expected.txt
)
set_tests_properties(
    Task2_Check3
    PROPERTIES DEPENDS Task2_Test3
)

add_test(
    NAME Task2_Test4
    COMMAND task2
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2_4.txt
            ${CMAKE_CURRENT_BINARY_DIR}/task2_4_output.txt
)
add_test(
    NAME Task2_Check4
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/task2_4_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2_4_expected.txt
)
set_tests_properties(
    Task2_Check4
    PROPERTIES DEPENDS Task2_Test4
)

add_test(
    NAME Task2_Test5
    COMMAND task2
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2_5.txt
            ${CMAKE_CURRENT_BINARY_DIR}/task2_5_output.txt
)
add_test(
    NAME Task2_Check5
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/task2_5_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2_5_expected.txt
)
set_tests_properties(
    Task2_Check5
    PROPERTIES DEPENDS Task2_Test5
)

add_test(
    NAME Task2_Test6
    COMMAND task2
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2_6.txt
            ${CMAKE_CURRENT_BINARY_DIR}/task2_6_output.txt
)
add_test(
    NAME Task2_Check6
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/task2_6_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2_6_expected.txt
)
set_tests_properties(
    Task2_Check6
    PROPERTIES DEPENDS Task2_Test6
)

add_custom_target(test_all
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --output-on-failure
    DEPENDS task1 task2
    COMMENT "Running all tests..."
)