add_executable(Lab2JollyScript jollyscript.cpp)
target_include_directories(Lab2JollyScript PRIVATE ../LibraryCPPTemplate)

function(add_jolly_test name script input expected)
    add_test(NAME ${name}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:Lab2JollyScript>"
            "-DSCRIPT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${script}"
            "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${input}"
            "-DEXPECTED=${expected}"
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/check-output.cmake)
endfunction()

add_jolly_test(TestJollyHello hello.jolly unused.txt "Hello World!")
add_jolly_test(TestJollyAdd add.jolly unused.txt "0")
add_jolly_test(TestJollyHexInput hex_input.jolly hex_input.txt "A")
add_jolly_test(TestJollyCharInput char_input.jolly char_input.txt "Z")
add_jolly_test(TestJollySubtraction subtract.jolly unused.txt "F")
add_jolly_test(TestJollyPeek peek.jolly unused.txt "AA")
add_jolly_test(TestJollyCommaKeep comma_keep.jolly unused.txt "AA")
add_jolly_test(TestJollySwapDrop swap_drop.jolly unused.txt "12")
add_jolly_test(TestJollyCondition condition.jolly unused.txt "0")
add_jolly_test(TestJollyHexEOF hex_input.jolly empty.txt "0")