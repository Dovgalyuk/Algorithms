enable_testing()

function(add_annoying_test test_name script_file input_file expected_output)
    add_test(
        NAME ${test_name}
        COMMAND annoying_interpreter ${script_file} ${input_file}
    )
endfunction()

add_annoying_test(test_example "input.annoying" "input.in" "C\nB\nA")
add_annoying_test(test_hello "hello.annoying" "hello.in" "Hello, World")
add_annoying_test(test_cat "cat.annoying" "cat.in" "Hello from input!")
add_annoying_test(test_calc "calc.annoying" "calc.in" "8")
