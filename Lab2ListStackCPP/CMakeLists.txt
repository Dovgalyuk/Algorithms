add_executable(list_stack main.cpp)

target_include_directories(list_stack PRIVATE
    ${CMAKE_SOURCE_DIR}/LibraryCPP
)

target_link_libraries(list_stack PRIVATE LibraryCPP)

function(add_list_stack_test test_name input_file expected_file)
    add_test(
        NAME ${test_name}
        COMMAND ${CMAKE_COMMAND}
            -DPROGRAM=$<TARGET_FILE:list_stack>
            -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${input_file}
            -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/${expected_file}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/CheckOutput.cmake
    )
endfunction()

add_list_stack_test(
    ExpressionPriority
    input1.txt
    input1.expected.txt
)

add_list_stack_test(
    ExpressionBrackets
    input2.txt
    input2.expected.txt
)

add_list_stack_test(
    ExpressionNegativeResult
    input3.txt
    input3.expected.txt
)

add_list_stack_test(
    ExpressionDivisionAndMultiplication
    input4.txt
    input4.expected.txt
)

add_list_stack_test(
    ExpressionBracketsAndMultiplication
    input5.txt
    input5.expected.txt
)

add_list_stack_test(
    ExpressionLeftAssociativity
    input6.txt
    input6.expected.txt
)

add_list_stack_test(
    ErrorDivisionByZero
    input7.txt
    input7.expected.txt
)

add_list_stack_test(
    ErrorMissingOperand
    input8.txt
    input8.expected.txt
)

add_list_stack_test(
    ErrorUnclosedBracket
    input9.txt
    input9.expected.txt
)

add_list_stack_test(
    ErrorUnexpectedClosingBracket
    input10.txt
    input10.expected.txt
)

add_list_stack_test(
    ErrorDoubleOperator
    input11.txt
    input11.expected.txt
)

add_list_stack_test(
    ErrorUnknownOperator
    input12.txt
    input12.expected.txt
)

add_list_stack_test(
    ErrorMissingOperatorBeforeBracket
    input13.txt
    input13.expected.txt
)

add_list_stack_test(
    ErrorEmptyExpression
    input14.txt
    input14.expected.txt
)

add_list_stack_test(
    ErrorEmptyBrackets
    input15.txt
    input15.expected.txt
)

add_list_stack_test(
    ErrorAdjacentOperators
    input16.txt
    input16.expected.txt
)