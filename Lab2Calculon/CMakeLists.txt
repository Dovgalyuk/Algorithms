
add_executable(Calculon main.cpp)

target_include_directories(Calculon PRIVATE
    ${PROJECT_SOURCE_DIR}/LibraryCPPClass
)

target_link_libraries(Calculon PRIVATE LibraryCPPClass)

# Тест 1. Чтение данных и вычитание
add_test(
    NAME CalculonBasic
    COMMAND Calculon
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/basic.calc
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/basic.in
)
set_tests_properties(CalculonBasic PROPERTIES
    PASS_REGULAR_EXPRESSION "7"
)

# Тест 2. Пример из задания
add_test(
    NAME CalculonExample
    COMMAND Calculon
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/example.calc
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/example.in
)
set_tests_properties(CalculonExample PROPERTIES
    PASS_REGULAR_EXPRESSION
    "72 101 108 111 44 32 119 114 108 100 33 10"
)

# Тест 3. Арифметические операции
add_test(
    NAME CalculonArithmetic
    COMMAND Calculon
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/arithmetic.calc
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/arithmetic.in
)
set_tests_properties(CalculonArithmetic PROPERTIES
    PASS_REGULAR_EXPRESSION "7 15 4 3"
)

# Тест 4. Условные команды
add_test(
    NAME CalculonCondition
    COMMAND Calculon
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/condition.calc
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/condition.in
)
set_tests_properties(CalculonCondition PROPERTIES
    PASS_REGULAR_EXPRESSION "42 7"
)

# Тест 5. Циклы
add_test(
    NAME CalculonLoop
    COMMAND Calculon
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/loop.calc
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/loop.in
)
set_tests_properties(CalculonLoop PROPERTIES
    PASS_REGULAR_EXPRESSION "7 7 7"
)
