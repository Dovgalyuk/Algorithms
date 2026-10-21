cmake_minimum_required(VERSION 3.10)
project(LabCPP3 CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPPClass)

add_library(library STATIC
    ${LIB_DIR}/vector.cpp
    ${LIB_DIR}/queue.cpp
)
target_include_directories(library PUBLIC ${LIB_DIR})

add_executable(lab3 lab3.cpp)
target_link_libraries(lab3 library)

function(add_maze_test name)
    add_test(NAME ${name}
             COMMAND ${CMAKE_COMMAND}
                     -DPROGRAM=$<TARGET_FILE:lab3>
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