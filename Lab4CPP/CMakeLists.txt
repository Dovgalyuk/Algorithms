add_executable(Lab4CPPMaxFlow max_flow.cpp)
target_include_directories(Lab4CPPMaxFlow PRIVATE ../LibraryCPPTemplate)
target_link_libraries(Lab4CPPMaxFlow PRIVATE LibraryCPP)
target_compile_features(Lab4CPPMaxFlow PRIVATE cxx_std_17)

if(MSVC)
    target_compile_options(Lab4CPPMaxFlow PRIVATE /utf-8)
endif()

function(add_flow_test name file code)
    add_test(
        NAME ${name}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:Lab4CPPMaxFlow>"
            "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${file}.txt"
            "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/${file}.out"
            "-DEXPECTED_CODE=${code}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/check_flow.cmake"
    )
    set_tests_properties(${name} PROPERTIES TIMEOUT 10)
endfunction()

add_flow_test(TestLab4SingleEdge single_edge 0)
add_flow_test(TestLab4Bottleneck bottleneck 0)
add_flow_test(TestLab4SeveralPaths several_paths 0)
add_flow_test(TestLab4Classic classic 0)
add_flow_test(TestLab4ReversePath reverse_path 0)
add_flow_test(TestLab4OppositeEdges opposite_edges 0)
add_flow_test(TestLab4NoPath no_path 0)
add_flow_test(TestLab4ZeroCapacity zero_capacity 0)
add_flow_test(TestLab4Loops loops 0)
add_flow_test(TestLab4LargeCapacity large_capacity 0)
add_flow_test(TestLab4LargeGraph large_graph 0)
add_flow_test(TestLab4NegativeCapacity negative_capacity 1)
add_flow_test(TestLab4UnknownVertex unknown_vertex 1)
add_flow_test(TestLab4DuplicateVertex duplicate_vertex 1)
add_flow_test(TestLab4DuplicateEdge duplicate_edge 1)
add_flow_test(TestLab4SameTerminals same_terminals 1)
add_flow_test(TestLab4MissingData missing_data 1)
add_flow_test(TestLab4ExtraData extra_data 1)
add_flow_test(TestLab4Overflow overflow 1)
add_flow_test(TestLab4Empty empty 1)
