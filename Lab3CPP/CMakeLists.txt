cmake_minimum_required(VERSION 3.10)

project(Lab3CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(graph graph.cpp)

target_include_directories(graph PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP)
target_link_libraries(graph LibraryCPP)

enable_testing()

function(add_graph_test test_name test_file expected_output)
    add_test(
            NAME ${test_name}
            COMMAND graph ${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_file}
    )
    set_tests_properties(${test_name} PROPERTIES
            PASS_REGULAR_EXPRESSION "${expected_output}"
            TIMEOUT 10
    )
endfunction()

add_graph_test(test1_linear_path test1.txt "1 2 3 4 5")
add_graph_test(test2_direct_edge test2.txt "1 4")
add_graph_test(test3_equal_paths test3.txt "1 [23] 5")
add_graph_test(test4_no_path test4.txt "IMPOSSIBLE")
add_graph_test(test5_start_equals_finish test5.txt "2")
add_graph_test(test6_cycle test6.txt "1 [23] 4 5")
add_graph_test(test7_minimal test7.txt "1 2")
add_graph_test(test8_isolated_vertex test8.txt "IMPOSSIBLE")
add_graph_test(test9_tree test9.txt "1 3 7")
add_graph_test(test10_complete_graph test10.txt "1 4")
add_graph_test(test11_disconnected test11.txt "IMPOSSIBLE")
add_graph_test(test12_shortcut test12.txt "1 5 10")