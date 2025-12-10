cmake_minimum_required(VERSION 3.10)
project(Lab4CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FindShortestPaths main.cpp)

target_link_libraries(FindShortestPaths LibraryCPPTemplate::GraphLibrary)

enable_testing()

set(TEST_INPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/test_graph_input.txt)
set(TEST_EXPECTED_FILE ${CMAKE_CURRENT_SOURCE_DIR}/test_expected_output.txt)
set(TEST_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/test_output.txt)

add_test(NAME FindPathsTest
    COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:FindShortestPaths>
        -DINPUT=${TEST_INPUT_FILE}
        -DSTART=A
        -DEND=E
        -DOUTPUT=${TEST_OUTPUT_FILE}
        -DEXPECTED=${TEST_EXPECTED_FILE}
        -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
)