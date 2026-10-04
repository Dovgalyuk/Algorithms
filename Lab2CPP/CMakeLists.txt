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

function(add_error_test name file)
    add_test(
        NAME ${name}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:Lab2CPPExpression>"
            "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${file}.txt"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/check_error.cmake"
    )
endfunction()

add_error_test(TestLab2MissingNumber missing_number)
add_error_test(TestLab2OpenBracket open_bracket)
add_error_test(TestLab2CloseBracket close_bracket)
add_error_test(TestLab2DivisionByZero division_zero)
add_error_test(TestLab2UnknownSymbol unknown_symbol)
add_error_test(TestLab2AdjacentNumbers adjacent_numbers)
add_error_test(TestLab2EmptyBrackets empty_brackets)
add_error_test(TestLab2EmptyExpression empty)
add_error_test(TestLab2UnaryMinus unary_minus)
add_error_test(TestLab2NumberOverflow number_overflow)
add_error_test(TestLab2ResultOverflow result_overflow)
