set(LIBRARY_CPP_TEMPLATE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../LibraryCPPTemplate")

add_executable(even_difference even_difference.cpp)
add_executable(resistance resistance.cpp)

target_include_directories(
    even_difference
    PRIVATE
    "${LIBRARY_CPP_TEMPLATE_DIR}"
)

target_include_directories(
    resistance
    PRIVATE
    "${LIBRARY_CPP_TEMPLATE_DIR}"
)

add_test(
    NAME TestEvenDifference1
    COMMAND even_difference
            ${CMAKE_CURRENT_SOURCE_DIR}/data/even_1.txt
)

set_tests_properties(
    TestEvenDifference1
    PROPERTIES
    PASS_REGULAR_EXPRESSION "6"
)

add_test(
    NAME TestEvenDifference2
    COMMAND even_difference
            ${CMAKE_CURRENT_SOURCE_DIR}/data/even_2.txt
)

set_tests_properties(
    TestEvenDifference2
    PROPERTIES
    PASS_REGULAR_EXPRESSION "8"
)

add_test(
    NAME TestResistance1
    COMMAND resistance
            ${CMAKE_CURRENT_SOURCE_DIR}/data/resistance_1.txt
)

set_tests_properties(
    TestResistance1
    PROPERTIES
    PASS_REGULAR_EXPRESSION "1\\.000000"
)

add_test(
    NAME TestResistance2
    COMMAND resistance
            ${CMAKE_CURRENT_SOURCE_DIR}/data/resistance_2.txt
)

set_tests_properties(
    TestResistance2
    PROPERTIES
    PASS_REGULAR_EXPRESSION "5\\.000000"
)

add_test(
    NAME TestEvenDifference3
    COMMAND even_difference
            ${CMAKE_CURRENT_SOURCE_DIR}/data/even_3.txt
)

set_tests_properties(
    TestEvenDifference3
    PROPERTIES
    WILL_FAIL TRUE
)