add_executable(Lab2CPP main.cpp)
target_include_directories(Lab2CPP PRIVATE ../LibraryCPP)
target_link_libraries(Lab2CPP PRIVATE LibraryCPP)

enable_testing()

# Пример 1 из условия (YES)
add_test(
    NAME test_example1
    COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
)
set_property(
    TEST test_example1
    PROPERTY PASS_REGULAR_EXPRESSION
    "YES"
)

# Пример 2 из условия (NO)
add_test(
    NAME test_example2
    COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
)
set_property(
    TEST test_example2
    PROPERTY PASS_REGULAR_EXPRESSION
    "NO"
)

# тест 3: (YES)
add_test(
    NAME test_custom1
    COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt
)
set_property(
    TEST test_custom1
    PROPERTY PASS_REGULAR_EXPRESSION
    "YES"
)

# тест 4: (NO)
add_test(
    NAME test_custom2
    COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt
)
set_property(
    TEST test_custom2
    PROPERTY PASS_REGULAR_EXPRESSION
    "NO"
)

# тест 5: (NO)
add_test(
    NAME test_custom3
    COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt
)
set_property(
    TEST test_custom3
    PROPERTY PASS_REGULAR_EXPRESSION
    "NO"
)
