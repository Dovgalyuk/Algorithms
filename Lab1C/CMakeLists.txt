add_executable(AboveSum above_sum.c)
target_include_directories(AboveSum PRIVATE ../LibraryC)
target_link_libraries(AboveSum PRIVATE LibraryC)

add_executable(RLE rle.c)
target_include_directories(RLE PRIVATE ../LibraryC)
target_link_libraries(RLE PRIVATE LibraryC)

function(add_output_test test_name target input expected)
    add_test(
        NAME ${test_name}
        COMMAND ${CMAKE_COMMAND}
            -DPROGRAM=$<TARGET_FILE:${target}>
            -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/test_data/${input}
            -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/test_data/${expected}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/RunAndCompare.cmake
    )
endfunction()

add_output_test(TestAboveSumMixed AboveSum above_sum_mixed.txt above_sum_mixed.expected)
add_output_test(TestAboveSumNone AboveSum above_sum_none.txt above_sum_none.expected)
add_output_test(TestAboveSumEmpty AboveSum empty.txt above_sum_empty.expected)

add_output_test(TestRLESeveralRuns RLE rle_runs.txt rle_runs.expected)
add_output_test(TestRLEOneRun RLE rle_one_run.txt rle_one_run.expected)
add_output_test(TestRLEEmpty RLE empty.txt rle_empty.expected)
