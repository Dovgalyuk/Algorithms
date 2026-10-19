cmake_minimum_required(VERSION 3.15)

add_executable(calculon calculon.cpp)
target_include_directories(calculon PUBLIC ../LibraryCPP)
target_link_libraries(calculon LibraryCPP)

function(add_calculon_test NAME SCRIPT INPUT EXPECTED)
    add_test(NAME ${NAME}
        COMMAND calculon
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/scripts/${SCRIPT}
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/inputs/${INPUT})
    set_property(TEST ${NAME} PROPERTY PASS_REGULAR_EXPRESSION "^${EXPECTED}\r?\n$")
endfunction()

# add_calculon_error_test(<name> <script> <input> <part of the error message>)
function(add_calculon_error_test NAME SCRIPT INPUT MESSAGE)
    add_test(NAME ${NAME}
        COMMAND calculon
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/scripts/${SCRIPT}
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/inputs/${INPUT})
    set_property(TEST ${NAME} PROPERTY PASS_REGULAR_EXPRESSION "${MESSAGE}")
endfunction()

# 1. Example from the task: prints the characters of the greeting as numbers.
#    NB: the script has "peek peek" for the letter 'l', so 108 is printed twice
#    (the example in the task has 12 numbers, a literal run gives 13).
add_calculon_test(Calculon_Hello hello.txt empty.txt
    "72 101 108 108 111 44 32 119 114 108 100 33 10")

# 2. sub: the top value minus the bottom one (input - 5)
add_calculon_test(Calculon_Sub_Positive sub.txt in_12.txt "7")
add_calculon_test(Calculon_Sub_NegativeFraction sub.txt in_minus_3_5.txt "-8\\.5000")

# 3. add and mul, two values are read for each of them
add_calculon_test(Calculon_AddMul arith.txt in_2_3_4_5.txt "5 20")

# 4. div: the top value divided by the bottom one; 4 digits after the point
add_calculon_test(Calculon_Div div.txt in_9.txt "4\\.5000 0\\.3333")

# 5. sq and sqrt
add_calculon_test(Calculon_SqSqrt sqrt.txt in_minus_1_5.txt "2\\.2500 1\\.5000 1\\.4142")

# 6. cond: equal values run the block, different ones skip it
add_calculon_test(Calculon_Cond_Equal cond.txt in_5.txt "111 222")
add_calculon_test(Calculon_Cond_NotEqual cond.txt in_7.txt "222")

# cond compares numbers up to 4 digits after the point
add_calculon_test(Calculon_Cond_DifferentIn4thDigit cond_get2.txt in_4_32464_4_32466.txt "222")
add_calculon_test(Calculon_Cond_SameUpTo4Digits cond_get2.txt in_4_32464_4_32462.txt "111 222")

# 7. nested cond: both match / only the outer one / none
add_calculon_test(Calculon_CondNested_Both cond_nested.txt in_1_2.txt "10 20 30")
add_calculon_test(Calculon_CondNested_OuterOnly cond_nested.txt in_1_3.txt "20 30")
add_calculon_test(Calculon_CondNested_None cond_nested.txt in_5.txt "30")

# 8. setr + repeat: the body runs once and then is repeated as many times as setr said
add_calculon_test(Calculon_Loop loop.txt empty.txt "2 4 8 16")
add_calculon_test(Calculon_Loop_NoRepeats loop_once.txt empty.txt "2")

# 9. 0 / 0 and 1 / 0 are printed as nan and inf
add_calculon_test(Calculon_NanInf nan_inf.txt empty.txt "nan inf")

# 10. Errors: the program reports the problem
add_calculon_error_test(Calculon_Error_EmptyStack err_empty_stack.txt empty.txt "add: Not enough elements on the stack")
add_calculon_error_test(Calculon_Error_UnknownCommand err_unknown.txt empty.txt "foo: unknown command")
add_calculon_error_test(Calculon_Error_NoEnd err_no_end.txt in_5.txt "cond: no matching end")
add_calculon_error_test(Calculon_Error_NoInput sub.txt empty.txt "get: no more input data")
add_calculon_error_test(Calculon_Error_NoScriptFile missing_script.txt empty.txt "Error opening script file")