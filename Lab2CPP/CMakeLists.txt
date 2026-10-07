add_executable(JollyScript jollyscript.cpp)
target_include_directories(JollyScript PRIVATE ../LibraryCPP)
target_link_libraries(JollyScript PRIVATE LibraryCPP)

add_executable(TestLab2Containers tests/containers.cpp)
target_include_directories(TestLab2Containers PRIVATE ../LibraryCPP)
target_link_libraries(TestLab2Containers PRIVATE LibraryCPP)
add_test(NAME TestLab2Containers COMMAND TestLab2Containers)
set_tests_properties(TestLab2Containers PROPERTIES TIMEOUT 10)

# Run with both required files and compare stdout byte for byte.
function(add_jolly_test name)
    add_test(NAME JollyScript_${name}
        COMMAND ${CMAKE_COMMAND}
            -DPROGRAM=$<TARGET_FILE:JollyScript>
            -DSCRIPT=${CMAKE_CURRENT_SOURCE_DIR}/test_data/${name}.jolly
            -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/test_data/${name}.input
            -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/test_data/${name}.expected
            -DEXPECTED_ERROR=${ARGV1}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/RunAndCompare.cmake)
    set_tests_properties(JollyScript_${name} PROPERTIES TIMEOUT 10)
endfunction()

add_jolly_test(hello_world)
add_jolly_test(arithmetic)
add_jolly_test(hex_input)
add_jolly_test(byte_input)
add_jolly_test(printing)
add_jolly_test(comments)
add_jolly_test(branches)
add_jolly_test(condition_0)
add_jolly_test(condition_3)
add_jolly_test(directions)
add_jolly_test(return_loop)
add_jolly_test(cat)
add_jolly_test(cat_empty)
add_jolly_test(underflow "Empty stack")
add_jolly_test(invalid_hex "Invalid hexadecimal input")
add_jolly_test(unset_return "Return location is not set")
add_jolly_test(missing_start "exactly one")
add_jolly_test(multiple_starts "exactly one")
add_jolly_test(out_of_bounds "Cursor outside")
add_jolly_test(empty_script "Empty script")
add_jolly_test(crlf)
add_jolly_test(binary_input)
