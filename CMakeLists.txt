add_executable(AltSum alt_sum.cpp)
target_link_libraries(AltSum PRIVATE Library)

add_executable(MostFrequent most_frequent.cpp)
target_link_libraries(MostFrequent PRIVATE Library)

set(COMPARE_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/compare_test.cmake)

function(add_output_test test_name exe_target input_file expected_file)
    add_test(NAME ${test_name}
        COMMAND ${CMAKE_COMMAND}
            -DTEST_EXE=$<TARGET_FILE:${exe_target}>
            -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/${input_file}
            -DEXPECTED_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/${expected_file}
            -P ${COMPARE_SCRIPT}
    )
endfunction()

add_output_test(AltSumTest1 AltSum altsum_input1.txt altsum_expected1.txt)
add_output_test(AltSumTest2 AltSum altsum_input2.txt altsum_expected2.txt)
add_output_test(AltSumTest3 AltSum altsum_input3.txt altsum_expected3.txt)

add_output_test(MostFrequentTest1 MostFrequent freq_input1.txt freq_expected1.txt)
add_output_test(MostFrequentTest2 MostFrequent freq_input2.txt freq_expected2.txt)
add_output_test(MostFrequentTest3 MostFrequent freq_input3.txt freq_expected3.txt)
