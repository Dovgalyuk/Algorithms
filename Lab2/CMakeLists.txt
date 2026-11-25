add_executable(VM main.cpp)
target_link_libraries(VM PRIVATE LibraryCPPClass)

enable_testing()

function(add_vm_test name input expected)
    add_test(NAME ${name}
        COMMAND ${CMAKE_COMMAND}
            -DVM=$<TARGET_FILE:VM>
            -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${input}
            -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/${expected}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/check.cmake)
endfunction()

add_vm_test(example example.txt example.out)
add_vm_test(arithmetic arithmetic.txt arithmetic.out)
add_vm_test(variables variables.txt variables.out)
add_vm_test(swap swap.txt swap.out)
add_vm_test(error_return error_return.txt error_return.err)
add_vm_test(error_address_pop error_address_pop.txt error_address_pop.err)
