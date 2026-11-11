add_executable(vector_queue main.cpp)

target_include_directories(vector_queue PRIVATE
    ${CMAKE_SOURCE_DIR}/LibraryCPP
)

target_link_libraries(vector_queue PRIVATE LibraryCPP)

function(add_vector_queue_test test_name input_file expected_file)
    add_test(
        NAME ${test_name}
        COMMAND ${CMAKE_COMMAND}
            -DPROGRAM=$<TARGET_FILE:vector_queue>
            -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/Tests/${input_file}
            -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/Tests/${expected_file}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/CheckOutput.cmake
    )
endfunction()

add_vector_queue_test(
    MazeExample
    input1.txt
    input1.expected.txt
)

add_vector_queue_test(
    MazeHorizontal
    input2.txt
    input2.expected.txt
)

add_vector_queue_test(
    MazeDiagonal
    input3.txt
    input3.expected.txt
)

add_vector_queue_test(
    MazeWithTurn
    input4.txt
    input4.expected.txt
)

add_vector_queue_test(
    MazeLongPath
    input5.txt
    input5.expected.txt
)

add_vector_queue_test(
    MazeObstacles
    input6.txt
    input6.expected.txt
)