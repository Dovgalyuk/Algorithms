add_executable(Lab1CppTask1 task1.cpp array.cpp)
add_executable(Lab1CppTask2 task2.cpp array.cpp)
add_executable(Lab1CppTest test.cpp array.cpp)

target_include_directories(Lab1CppTask1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Lab1CppTask2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Lab1CppTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_test(
    NAME TestLab1CppArray
    COMMAND Lab1CppTest
)

set_property(
    TEST TestLab1CppArray
    PROPERTY PASS_REGULAR_EXPRESSION "1 2 3 4 5"
)

add_test(
    NAME TestLab1CppTask1_1
    COMMAND Lab1CppTask1
        ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
)

set_property(
    TEST TestLab1CppTask1_1
    PROPERTY PASS_REGULAR_EXPRESSION
        "31 28 31 30 31 30 31 31 30 31 30 31"
)

add_test(
    NAME TestLab1CppTask1_2
    COMMAND Lab1CppTask1
        ${CMAKE_CURRENT_SOURCE_DIR}/input1_2.txt
)

set_property(
    TEST TestLab1CppTask1_2
    PROPERTY PASS_REGULAR_EXPRESSION
        "62 56 62 60 62 60 62 62 60 62 60 62"
)

add_test(
    NAME TestLab1CppTask2_1
    COMMAND Lab1CppTask2
        ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
)

set_property(
    TEST TestLab1CppTask2_1
    PROPERTY PASS_REGULAR_EXPRESSION
        "2 3 5 7"
)

add_test(
    NAME TestLab1CppTask2_2
    COMMAND Lab1CppTask2
        ${CMAKE_CURRENT_SOURCE_DIR}/input2_2.txt
)

set_property(
    TEST TestLab1CppTask2_2
    PROPERTY PASS_REGULAR_EXPRESSION
        "2 9 11 13 17"
)