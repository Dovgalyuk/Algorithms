cmake_minimum_required(VERSION 3.16)
project(MazeLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(LIBRARY_HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPPTemplate")

add_executable(maze main.cpp)
target_include_directories(maze PRIVATE "${LIBRARY_HEADERS_DIR}")

include(CTest)
if(BUILD_TESTING)
    add_executable(test_vector tests/test_vector.cpp)
    target_include_directories(test_vector PRIVATE "${LIBRARY_HEADERS_DIR}")
    add_test(NAME vector_operations COMMAND test_vector)

    add_executable(test_queue tests/test_queue.cpp)
    target_include_directories(test_queue PRIVATE "${LIBRARY_HEADERS_DIR}")
    add_test(NAME queue_circular_buffer COMMAND test_queue)

    # Each maze is fed to standard input and its output compared exactly.
    function(add_maze_test test_name)
        add_test(NAME ${test_name}
            COMMAND "${CMAKE_COMMAND}"
                "-DPROGRAM=$<TARGET_FILE:maze>"
                "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_name}.in"
                "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_name}.out"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/tests/check.cmake"
        )
    endfunction()

    add_maze_test(maze_path)
    add_maze_test(maze_impossible)
    add_maze_test(maze_adjacent)
    add_maze_test(maze_corridor)
endif()
