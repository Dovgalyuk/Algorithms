cmake_minimum_required(VERSION 3.16)


project(AnnoyingScript)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    annoying
    main.cpp
)

target_include_directories(
    annoying
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPPTemplate
    
)

enable_testing()


# Тест 1
add_test(
    NAME Annoying_Hello
    COMMAND annoying
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/script1.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/input1.txt
)

set_tests_properties(
    Annoying_Hello
    PROPERTIES
    PASS_REGULAR_EXPRESSION "STACK: \\[Hello\\]"
)


# Тест 2
add_test(
    NAME Annoying_Input
    COMMAND annoying
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/script2.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/input2.txt
)

set_tests_properties(
    Annoying_Input
    PROPERTIES
    PASS_REGULAR_EXPRESSION "STACK: \\[Hello World\\]"
)


# Тест 3
add_test(
    NAME Annoying_Stack
    COMMAND annoying
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/script3.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/input3.txt
)

set_tests_properties(
    Annoying_Stack
    PROPERTIES
    PASS_REGULAR_EXPRESSION "STACK: \\[C, B, A\\]"
)


# Тест 4
add_test(
    NAME Annoying_Math
    COMMAND annoying
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/script4.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/input4.txt
)

set_tests_properties(
    Annoying_Math
    PROPERTIES
    PASS_REGULAR_EXPRESSION "STACK: \\[8\\]"
)
# Тест 5 — добавление символа
add_test(
    NAME Annoying_Push
    COMMAND annoying
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/script5.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/input5.txt"
)

set_tests_properties(
    Annoying_Push PROPERTIES
    PASS_REGULAR_EXPRESSION "STACK: \\[A\\]"
)

# Тест 6 — добавление строки
add_test(
    NAME Annoying_String
    COMMAND annoying
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/script6.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/input6.txt"
)

set_tests_properties(
    Annoying_String PROPERTIES
    PASS_REGULAR_EXPRESSION "STACK: \\[Hello Test\\]"
)
