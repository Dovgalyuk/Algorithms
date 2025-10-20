add_executable(Lab2CPPClass calculon.cpp)
target_include_directories(Lab2CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPPClass LibraryCPPClass)

# Original test
add_test(NAME TestCalculonBasic
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/test_combined.txt)

set_tests_properties(TestCalculonBasic PROPERTIES
    PASS_REGULAR_EXPRESSION ""
)

# Arithmetic operations tests
add_test(NAME TestCalculonArithmetic
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/test_arithmetic.txt)

set_tests_properties(TestCalculonArithmetic PROPERTIES
    PASS_REGULAR_EXPRESSION "15 16 45 0"
)

# Mathematical functions tests
add_test(NAME TestCalculonMathFunctions
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/test_math_functions.txt)

set_tests_properties(TestCalculonMathFunctions PROPERTIES
    PASS_REGULAR_EXPRESSION "5 4 81 36"
)

# Get command test
add_test(NAME TestCalculonGet
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/test_get_command.txt)

set_tests_properties(TestCalculonGet PROPERTIES
    PASS_REGULAR_EXPRESSION "1 2 3 4 5"
)

# Conditional logic test
add_test(NAME TestCalculonConditional
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/test_conditional.txt)

set_tests_properties(TestCalculonConditional PROPERTIES
    PASS_REGULAR_EXPRESSION "1 1"
)

# Loop functionality test
add_test(NAME TestCalculonLoop
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/test_loop_simple.txt)

set_tests_properties(TestCalculonLoop PROPERTIES
    PASS_REGULAR_EXPRESSION "5"
)

# Complex operations test
add_test(NAME TestCalculonComplex
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/test_complex.txt)

set_tests_properties(TestCalculonComplex PROPERTIES
    PASS_REGULAR_EXPRESSION "4 625 156"
)