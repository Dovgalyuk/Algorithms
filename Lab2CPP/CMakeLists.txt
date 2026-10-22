
add_executable(jolly jolly.cpp)
target_link_libraries(jolly PRIVATE LibraryCPPTemplate)

function(add_jolly_test name)
    add_test(
        NAME ${name}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:jolly>"
            "-DSCRIPT=${CMAKE_CURRENT_SOURCE_DIR}/Tests/${name}.jolly"
            "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/Tests/${name}.input"
            "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/Tests/${name}.expected"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/Tests/RunTest.cmake"
    )
endfunction()

add_jolly_test(push_hex)
add_jolly_test(addition)
add_jolly_test(subtraction)
add_jolly_test(duplicate)
add_jolly_test(hex_input)
add_jolly_test(byte_input)
add_jolly_test(printing)
add_jolly_test(comments)
add_jolly_test(newline)
add_jolly_test(branches)
add_jolly_test(hello_world)
