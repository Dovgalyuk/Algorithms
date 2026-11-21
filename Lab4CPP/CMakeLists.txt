add_executable(Lab4CPP main.cpp)

target_include_directories(Lab4CPP PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPPTemplate"
)

target_compile_features(Lab4CPP PRIVATE cxx_std_17)

# Тест 1 Обход дорогих клеток
# Вход:
# 2 4
# 1 90 90 1
# 1 1 1 1
# 0 0 0 3
#
# Ожидаемый вывод:
# 5
# 0 0
# 1 0
# 1 1
# 1 2
# 1 3
# 0 3
add_test(
    NAME TestLabCPP4Detour
    COMMAND Lab4CPP "${CMAKE_CURRENT_SOURCE_DIR}/detour.txt"
)

set_tests_properties(TestLabCPP4Detour PROPERTIES
    PASS_REGULAR_EXPRESSION "^5\n0 0\n1 0\n1 1\n1 2\n1 3\n0 3\n$"
)

# Тест 2 Старт совпадает с целью
# Вход:
# 1 1
# 9
# 0 0 0 0
#
# Ожидаемый вывод:
# 0
# 0 0
add_test(
    NAME TestLabCPP4Single
    COMMAND Lab4CPP "${CMAKE_CURRENT_SOURCE_DIR}/single.txt"
)

set_tests_properties(TestLabCPP4Single PROPERTIES
    PASS_REGULAR_EXPRESSION "^0\n0 0\n$"
)

# Тест 3 Маршрут с нулевой стоимостью
# Вход:
# 1 3
# 5 0 0
# 0 0 0 2
#
# Ожидаемый вывод:
# 0
# 0 0
# 0 1
# 0 2
add_test(
    NAME TestLabCPP4Zero
    COMMAND Lab4CPP "${CMAKE_CURRENT_SOURCE_DIR}/zero.txt"
)

set_tests_properties(TestLabCPP4Zero PROPERTIES
    PASS_REGULAR_EXPRESSION "^0\n0 0\n0 1\n0 2\n$"
)

# Тест 4. Отрицательная стоимость клетки.
# Вход:
# 1 2
# 1 -2
# 0 0 0 1
#
# Ожидаемое сообщение:
# Expected a non-negative cell cost
add_test(
    NAME TestLabCPP4Invalid
    COMMAND Lab4CPP "${CMAKE_CURRENT_SOURCE_DIR}/invalid.txt"
)

set_tests_properties(TestLabCPP4Invalid PROPERTIES
    PASS_REGULAR_EXPRESSION "^Стоимость клетки должна быть неотрицательным целым числом\n$"
)