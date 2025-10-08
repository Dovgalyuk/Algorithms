add_executable(Lab2 lab2.cpp)

target_include_directories(Lab2 BEFORE PRIVATE ../LibraryCPPTemplate)

function(add_lab2_test name input expected)
    add_test(NAME ${name}
             COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/${input})
    set_tests_properties(${name}
        PROPERTIES PASS_REGULAR_EXPRESSION "${expected}")
endfunction()

add_lab2_test(Lab2SampleValid input1.txt YES)
add_lab2_test(Lab2CrossingQuotesInvalid input2.txt NO)
add_lab2_test(Lab2SingleQuotesValid input3.txt YES)
add_lab2_test(Lab2CurlyQuotesValid input4.txt YES)
add_lab2_test(Lab2SampleInvalid input5.txt NO)