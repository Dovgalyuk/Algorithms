add_executable(forth forth.cpp)

target_compile_features(forth PRIVATE cxx_std_11)

target_include_directories(
    forth
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPPTemplate"
)

function(add_forth_test name expected_output expected_code expected_error)
    set(expected_base "${CMAKE_CURRENT_BINARY_DIR}/${name}")

    file(WRITE "${expected_base}.out" "${expected_output}")
    file(WRITE "${expected_base}.err" "${expected_error}")

    add_test(
        NAME Forth_${name}
        COMMAND "${CMAKE_COMMAND}"
            "-DPROGRAM=$<TARGET_FILE:forth>"
            "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/data/${name}.txt"
            "-DEXPECTED_BASE=${expected_base}"
            "-DEXPECTED_CODE=${expected_code}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/check_test.cmake"
    )

    set_tests_properties(Forth_${name} PROPERTIES TIMEOUT 10)
endfunction()

# Examples from the assignment
add_forth_test(example_rot "1\n3\n2\n" 0 "")
add_forth_test(example_dup "1\n2\n3\n6\n" 0 "")

# Arithmetic operations
add_forth_test(add "5\n" 0 "")
add_forth_test(subtract "-5\n" 0 "")
add_forth_test(multiply "20\n" 0 "")
add_forth_test(divide "4\n" 0 "")
add_forth_test(modulo "1\n" 0 "")

# Stack operations
add_forth_test(drop "1\n" 0 "")
add_forth_test(swap "1\n2\n" 0 "")
add_forth_test(over "1\n2\n1\n" 0 "")

# An empty script is valid
add_forth_test(empty_input "" 0 "")

# Invalid scripts
add_forth_test(empty_stack "" 1 "Stack is empty\n")
add_forth_test(missing_operand "" 1 "Stack is empty\n")
add_forth_test(division_zero "" 1 "Division by zero\n")
add_forth_test(modulo_zero "" 1 "Division by zero\n")
add_forth_test(unknown "" 1 "Unknown command: hello\n")
add_forth_test(overflow "" 1 "Integer overflow\n")