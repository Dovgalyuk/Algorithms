add_executable(Laba3CPP main.cpp)
target_include_directories(Laba3CPP PRIVATE ../LibraryCPPTemplate)

function(add_laba3_test name input expected mode)
    add_test(NAME ${name}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:Laba3CPP>"
            "-DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/Tests/${input}"
            "-DEXPECTED_FILE=${CMAKE_CURRENT_SOURCE_DIR}/Tests/${expected}"
            "-DMODE=${mode}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/Tests/check.cmake")
endfunction()

add_laba3_test(TestLaba3Example example.txt example.out file)
add_laba3_test(TestLaba3Branches branches.txt branches.out file)
add_laba3_test(TestLaba3Unreachable unreachable.txt empty.out file)
add_laba3_test(TestLaba3Whitespace whitespace.txt whitespace.out stdin)
add_laba3_test(TestLaba3SelfReaction self.txt self.out file)
