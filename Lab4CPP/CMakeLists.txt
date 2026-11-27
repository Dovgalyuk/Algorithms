cmake_minimum_required(VERSION 3.10)

project(Lab4CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dijkstra dijkstra.cpp)

target_include_directories(dijkstra PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPPTemplate)

enable_testing()

function(add_dijkstra_test test_name test_file expected_output)
    add_test(
            NAME ${test_name}
            COMMAND dijkstra ${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_file}
    )
    set_tests_properties(${test_name} PROPERTIES
            PASS_REGULAR_EXPRESSION "${expected_output}"
            TIMEOUT 10
    )
endfunction()

add_dijkstra_test(test_linear_path linear_path.txt "A B C D E")
add_dijkstra_test(test_direct_edge direct_edge.txt "X Y")
add_dijkstra_test(test_equal_paths equal_paths.txt "A B E")
add_dijkstra_test(test_no_path no_path.txt "IMPOSSIBLE")
add_dijkstra_test(test_start_equals_finish start_equals_finish.txt "A")
add_dijkstra_test(test_cycle cycle.txt "A D")
add_dijkstra_test(test_minimal minimal.txt "1 2")
add_dijkstra_test(test_isolated_vertex isolated_vertex.txt "IMPOSSIBLE")
add_dijkstra_test(test_tree tree.txt "A B D")
add_dijkstra_test(test_complete_graph complete_graph.txt "A B C D")
add_dijkstra_test(test_disconnected disconnected.txt "IMPOSSIBLE")
add_dijkstra_test(test_shortcut shortcut.txt "A C D E")
add_dijkstra_test(test_star_graph star_graph.txt "A E")
add_dijkstra_test(test_chain_with_bypass chain_with_bypass.txt "A D")
add_dijkstra_test(test_single_edge single_edge.txt "A B")
add_dijkstra_test(test_square_grid square_grid.txt "A B D")
add_dijkstra_test(test_long_path long_path.txt "1 2 3 4 5 6 7 8 9 10")
add_dijkstra_test(test_multiple_shortest multiple_shortest.txt "A B D")
add_dijkstra_test(test_heavy_weights heavy_weights.txt "A C B")
add_dijkstra_test(test_zero_weight zero_weight.txt "A B")