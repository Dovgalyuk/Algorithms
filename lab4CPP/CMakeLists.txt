cmake_minimum_required(VERSION 3.10)
project(Lab4App)


add_executable(main_program main.cpp)


target_include_directories(main_program PRIVATE 
    ${CMAKE_SOURCE_DIR}/LibraryCPPTemplate
)


enable_testing()


function(add_dijkstra_test test_name input_file expected_file)
    add_test(NAME ${test_name} 
        COMMAND ${CMAKE_COMMAND} 
            -DPROGRAM_EXE=$<TARGET_FILE:main_program>
            -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/${input_file}
            -DEXPECTED_FILE=${CMAKE_CURRENT_SOURCE_DIR}/${expected_file}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/check_output.cmake
    )
endfunction()

add_dijkstra_test(DijkstraConnected    "connected.txt"     "connected_expected.txt")
add_dijkstra_test(DijkstraDisconnected "disconnected.txt"  "disconnected_expected.txt")
add_dijkstra_test(DijkstraSingleVertex "single_vertex.txt" "single_vertex_expected.txt")