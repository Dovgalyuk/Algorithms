add_executable(FordFulkerson ford_fulkerson.cpp)
target_include_directories(FordFulkerson PUBLIC ../LibraryCPPTemplate)

foreach(test_name simple bidir zero bypass cross grid ten)
    add_test(NAME FordFulkerson_${test_name} COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:FordFulkerson>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/Test/sample_${test_name}.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/Test/sample_${test_name}_expected.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/Test/OutputCheck.cmake)
endforeach()