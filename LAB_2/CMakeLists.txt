add_executable(Lab2MergeSort merge_sort.cpp)
target_include_directories(Lab2MergeSort PRIVATE ../LibraryCPPClass)
target_link_libraries(Lab2MergeSort PRIVATE LibraryCPPClass)
target_compile_features(Lab2MergeSort PRIVATE cxx_std_11)
target_compile_definitions(Lab2MergeSort PRIVATE DEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")

function(sort_test name input expected status)
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${name}.txt" "${input}")
    add_test(NAME ${name} COMMAND ${CMAKE_COMMAND}
        "-DPROGRAM=$<TARGET_FILE:Lab2MergeSort>"
        "-DINPUT=${CMAKE_CURRENT_BINARY_DIR}/${name}.txt"
        "-DEXPECTED=${expected}"
        "-DSTATUS=${status}"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
endfunction()

add_test(NAME MergeExample COMMAND ${CMAKE_COMMAND}
    "-DPROGRAM=$<TARGET_FILE:Lab2MergeSort>"
    "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
    "-DEXPECTED=5 12 34" -DSTATUS=0
    -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
sort_test(MergeReverse "9 8 7 6 5 4 3 2 1" "1 2 3 4 5 6 7 8 9" 0)
sort_test(MergeDuplicates "3 -1 3 0 -1 2 2" "-1 -1 0 2 2 3 3" 0)
sort_test(MergeSorted "-3 0 2 8" "-3 0 2 8" 0)
sort_test(MergeSingle "42" "42" 0)
sort_test(MergeEmpty "" "" 0)
sort_test(MergeInvalid "12 abc 5" "" 1)
sort_test(MergeOverflow "12 999999999999999999999" "" 1)
