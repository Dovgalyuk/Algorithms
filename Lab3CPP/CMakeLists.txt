cmake_minimum_required(VERSION 3.20)

project(Lab3CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab3CPP main.cpp)

target_link_libraries(Lab3CPP PRIVATE LibraryCPP)

enable_testing()

function(add_maze_test number)
    add_test(
            NAME maze_test${number}
            COMMAND ${CMAKE_COMMAND}
            -DPROGRAM=$<TARGET_FILE:Lab3CPP>
            -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/test_maze${number}.txt
            -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/test_maze${number}.out
            -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/test_maze${number}.result
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_maze_test.cmake
    )
endfunction()

add_maze_test(1)
add_maze_test(2)
add_maze_test(3)
add_maze_test(4)
add_maze_test(5)
add_maze_test(6)
