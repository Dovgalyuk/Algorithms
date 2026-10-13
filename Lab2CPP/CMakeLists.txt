cmake_minimum_required(VERSION 3.27)

project(Lab2CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab2CPP MiniPig.cpp)

target_include_directories(Lab2CPP PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP)

target_link_libraries(Lab2CPP LibraryCPP)

enable_testing()

function(add_minipig_test test_name script_file input_file expected_output)
    add_test(
            NAME ${test_name}
            COMMAND Lab2CPP
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/${script_file}
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/${input_file}
    )
    set_tests_properties(${test_name} PROPERTIES
            PASS_REGULAR_EXPRESSION "${expected_output}"
    )
endfunction()

add_minipig_test(
        test_push_output
        test_push_output.txt
        test_push_output_input.txt
        "1"
)

add_minipig_test(
        test_subtraction_zero
        test_subtraction_zero.txt
        test_subtraction_zero_input.txt
        "0"
)

add_minipig_test(
        test_subtraction_negative
        test_subtraction_negative.txt
        test_subtraction_negative_input.txt
        "-1"
)

add_minipig_test(
        test_input_output
        test_input_output.txt
        test_input_output_input.txt
        "42"
)

add_minipig_test(
        test_register
        test_register.txt
        test_register_input.txt
        "1"
)

add_minipig_test(
        test_swap
        test_swap.txt
        test_swap_input.txt
        "10"
)

add_minipig_test(
        test_switch_stacks
        test_switch_stacks.txt
        test_switch_stacks_input.txt
        "1.*1"
)

add_minipig_test(
        test_reverse
        test_reverse.txt
        test_reverse_input.txt
        "10"
)

add_minipig_test(
        test_flag
        test_flag.txt
        test_flag_input.txt
        "11"
)

add_minipig_test(
        test_goto_forward
        test_goto_forward.txt
        test_goto_forward_input.txt
        "1"
)

add_minipig_test(
        test_char_input_output
        test_char_input_output.txt
        test_char_input_output_input.txt
        "A"
)

add_minipig_test(
        test_multiple_operations
        test_multiple_operations.txt
        test_multiple_operations_input.txt
        "-2"
)

add_minipig_test(
        test_professor_example
        test_prof_script.txt
        test_professor_input.txt
        "1 1[\r\n]+1 1 1"
)