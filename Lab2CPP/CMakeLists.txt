add_executable(Lab2CPPExpression expression.cpp)
target_include_directories(Lab2CPPExpression PRIVATE ../LibraryCPP)
target_link_libraries(Lab2CPPExpression PRIVATE LibraryCPP)
target_compile_features(Lab2CPPExpression PRIVATE cxx_std_17)

add_executable(TestLab2Containers containers_test.cpp)
target_include_directories(TestLab2Containers PRIVATE ../LibraryCPP)
target_link_libraries(TestLab2Containers PRIVATE LibraryCPP)
target_compile_features(TestLab2Containers PRIVATE cxx_std_17)
add_test(NAME TestLab2Containers COMMAND TestLab2Containers)
set_tests_properties(TestLab2Containers PROPERTIES TIMEOUT 10)

if(MSVC)
    target_compile_options(Lab2CPPExpression PRIVATE /utf-8)
endif()

add_test(NAME TestLab2Priority COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/priority.txt")
set_tests_properties(TestLab2Priority PROPERTIES PASS_REGULAR_EXPRESSION "^6[\r\n]*$")

add_test(NAME TestLab2Parentheses COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/parentheses.txt")
set_tests_properties(TestLab2Parentheses PROPERTIES PASS_REGULAR_EXPRESSION "^5[\r\n]*$")

add_test(NAME TestLab2Negative COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/negative.txt")
set_tests_properties(TestLab2Negative PROPERTIES PASS_REGULAR_EXPRESSION "^-3[\r\n]*$")

add_test(NAME TestLab2Nested COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/nested.txt")
set_tests_properties(TestLab2Nested PROPERTIES PASS_REGULAR_EXPRESSION "^36[\r\n]*$")

add_test(NAME TestLab2Spaces COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/spaces.txt")
set_tests_properties(TestLab2Spaces PROPERTIES PASS_REGULAR_EXPRESSION "^27[\r\n]*$")

add_test(NAME TestLab2Division COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/division.txt")
set_tests_properties(TestLab2Division PROPERTIES PASS_REGULAR_EXPRESSION "^3[\r\n]*$")

add_test(NAME TestLab2LeftOrder COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/left_order.txt")
set_tests_properties(TestLab2LeftOrder PROPERTIES PASS_REGULAR_EXPRESSION "^4[\r\n]*$")

add_test(NAME TestLab2Zero COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/zero.txt")
set_tests_properties(TestLab2Zero PROPERTIES PASS_REGULAR_EXPRESSION "^0[\r\n]*$")

add_test(NAME TestLab2IntLimit COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/int_limit.txt")
set_tests_properties(TestLab2IntLimit PROPERTIES PASS_REGULAR_EXPRESSION "^2147483647[\r\n]*$")

add_test(NAME TestLab2NegativeDivision COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/negative_division.txt")
set_tests_properties(TestLab2NegativeDivision PROPERTIES PASS_REGULAR_EXPRESSION "^-2[\r\n]*$")

add_test(NAME TestLab2MissingNumber COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/missing_number.txt")
add_test(NAME TestLab2OpenBracket COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/open_bracket.txt")
add_test(NAME TestLab2CloseBracket COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/close_bracket.txt")
add_test(NAME TestLab2DivisionByZero COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/division_zero.txt")
add_test(NAME TestLab2UnknownSymbol COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/unknown_symbol.txt")
add_test(NAME TestLab2AdjacentNumbers COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/adjacent_numbers.txt")
add_test(NAME TestLab2EmptyBrackets COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/empty_brackets.txt")
add_test(NAME TestLab2EmptyExpression COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/empty.txt")
add_test(NAME TestLab2UnaryMinus COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/unary_minus.txt")
add_test(NAME TestLab2NumberOverflow COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/number_overflow.txt")
add_test(NAME TestLab2ResultOverflow COMMAND Lab2CPPExpression "${CMAKE_CURRENT_SOURCE_DIR}/tests/result_overflow.txt")

set_tests_properties(
    TestLab2MissingNumber TestLab2OpenBracket TestLab2CloseBracket
    TestLab2DivisionByZero TestLab2UnknownSymbol TestLab2AdjacentNumbers
    TestLab2EmptyBrackets TestLab2EmptyExpression TestLab2UnaryMinus
    TestLab2NumberOverflow TestLab2ResultOverflow
    PROPERTIES WILL_FAIL TRUE
)
