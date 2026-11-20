# 1
add_executable(means means.cpp)
target_include_directories(means PRIVATE ../LibraryCPP)
target_link_libraries(means PRIVATE LibraryCPP)

function(add_means_test test_name input_file expected_file)
    add_test(
        NAME ${test_name}
        COMMAND ${CMAKE_COMMAND}
            -DPROGRAM=$<TARGET_FILE:means>
            -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${input_file}
            -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/${expected_file}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/CheckOutput.cmake
    )
endfunction()

add_means_test(
    MeansMixed
    input1.txt
    input1.expected.txt
)

add_means_test(
    MeansOnlyPositive
    input2.txt
    input2.expected.txt
)

add_means_test(
    MeansOnlyNegative
    input3.txt
    input3.expected.txt
)

add_means_test(
    MeansOnlyZeros
    input4.txt
    input4.expected.txt
)



# 2
add_executable(indivisible indivisible.cpp)

target_include_directories(indivisible PRIVATE ../LibraryCPP)

target_link_libraries(indivisible PRIVATE LibraryCPP)

function(add_indivisible_test test_name input_file expected_file)
    add_test(
        NAME ${test_name}
        COMMAND ${CMAKE_COMMAND}
            -DPROGRAM=$<TARGET_FILE:indivisible>
            -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${input_file}
            -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/${expected_file}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/CheckOutput.cmake
    )
endfunction()

add_indivisible_test(
    IndivisibleBasic
    div1.txt
    div1.expected.txt
)

add_indivisible_test(
    IndivisibleWithOne
    div2.txt
    div2.expected.txt
)

add_indivisible_test(
    IndivisibleDuplicates
    div3.txt
    div3.expected.txt
)

add_indivisible_test(
    IndivisibleWithZero
    div4.txt
    div4.expected.txt
)

