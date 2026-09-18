add_executable(Lab1CPPMonthly proga_2.cpp)
target_include_directories(Lab1CPPMonthly PUBLIC ../LibraryCPPTemplate)

add_executable(Lab1CPPCompress proga_1.cpp)
target_include_directories(Lab1CPPCompress PUBLIC ../LibraryCPPTemplate)

add_test(
    NAME TestLab1CPPMonthlyConstant
    COMMAND Lab1CPPMonthly ${CMAKE_CURRENT_SOURCE_DIR}/examples/monthly_constant.txt
)
set_property(
    TEST TestLab1CPPMonthlyConstant
    PROPERTY PASS_REGULAR_EXPRESSION "31 28 31 30 31 30 31 31 30 31 30 31"
)

add_test(
    NAME TestLab1CPPMonthlyPattern
    COMMAND Lab1CPPMonthly ${CMAKE_CURRENT_SOURCE_DIR}/examples/monthly_pattern.txt
)
set_property(
    TEST TestLab1CPPMonthlyPattern
    PROPERTY PASS_REGULAR_EXPRESSION "496 1274 2325 3165 4216 4995 6107 7068 7755 8959 9585 10850"
)

add_test(
    NAME TestLab1CPPCompressMixed
    COMMAND Lab1CPPCompress ${CMAKE_CURRENT_SOURCE_DIR}/examples/compress_mixed_values.txt
)
set_property(
    TEST TestLab1CPPCompressMixed
    PROPERTY PASS_REGULAR_EXPRESSION "-5 0 3 30 35 40 0 0 0 0 0 0"
)

add_test(
    NAME TestLab1CPPCompressAllRemoved
    COMMAND Lab1CPPCompress ${CMAKE_CURRENT_SOURCE_DIR}/examples/compress_all_removed.txt
)
set_property(
    TEST TestLab1CPPCompressAllRemoved
    PROPERTY PASS_REGULAR_EXPRESSION "0 0 0 0 0 0 0 0"
)

add_test(
    NAME TestLab1CPPCompressNoRemoved
    COMMAND Lab1CPPCompress ${CMAKE_CURRENT_SOURCE_DIR}/examples/compress_no_removed.txt
)
set_property(
    TEST TestLab1CPPCompressNoRemoved
    PROPERTY PASS_REGULAR_EXPRESSION "1 3 5 7 9 11 13"
)
