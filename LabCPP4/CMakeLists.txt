cmake_minimum_required(VERSION 3.10)
project(LabCPP4 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

set(LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPPTemplate)

add_executable(FloydDemo Floid.cpp)
target_include_directories(FloydDemo PUBLIC ${LIB_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

function(add_maze_test name)
    add_test(NAME ${name}
             COMMAND ${CMAKE_COMMAND}
                     -DPROGRAM=$<TARGET_FILE:FloydDemo>
                     -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/${name}.txt
                     -DEXPECTED_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/${name}exp.txt
                     -DTESTNAME=${name}
                     -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake)
endfunction()

add_maze_test(test1)
add_maze_test(test2)
add_maze_test(test3)
add_maze_test(test4)
add_maze_test(test5)
add_maze_test(test6)
add_maze_test(test7)