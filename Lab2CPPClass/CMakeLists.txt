add_executable(AnnoyingScriptInterpreter main.cpp)
target_include_directories(AnnoyingScriptInterpreter PUBLIC ../LibraryCPPClass)
target_link_libraries(AnnoyingScriptInterpreter LibraryCPPClass)

function(add_annoying_test test_name script_file input_file expected_output)
    add_test(
        NAME ${test_name}
        COMMAND AnnoyingScriptInterpreter
        ${CMAKE_CURRENT_SOURCE_DIR}/Tests/${script_file}
        ${CMAKE_CURRENT_SOURCE_DIR}/Tests/${input_file}
    )
    set_property(
        TEST ${test_name}
        PROPERTY PASS_REGULAR_EXPRESSION "${expected_output}"
    )
endfunction()

add_annoying_test(test_example "input.annoying" "input.in" "C\r?\nB\r?\nA")
add_annoying_test(test_hello "hello.annoying" "hello.in" "Hello, World")
add_annoying_test(test_cat "cat.annoying" "cat.in" "Hello from input!")
add_annoying_test(test_calc "calc.annoying" "calc.in" "8")
add_annoying_test(test_join "join.annoying" "join.in" "^Stack\r?\n?$")
add_annoying_test(test_pop "pop.annoying" "pop.in" "^2\r?\n1\r?\n?$")
add_annoying_test(test_math "math.annoying" "math.in" "^42\r?\n?$")
add_annoying_test(test_branch "branch.annoying" "branch.in" "^OK\r?\n?$")