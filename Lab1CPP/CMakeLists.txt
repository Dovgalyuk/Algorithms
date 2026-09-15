
cmake_minimum_required(VERSION 3.16)

project(Lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lab1
    lab1.cpp
    array.cpp
    array.h
)

enable_testing()

add_test(
    NAME sieve_test_1
    COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:lab1>
        -DMODE=sieve
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/sieve_1.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/sieve_1.expected
        -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/sieve_1.actual
        -P ${CMAKE_CURRENT_SOURCE_DIR}/test.cmake
)

add_test(
    NAME sieve_test_2
    COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:lab1>
        -DMODE=sieve
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/sieve_2.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/sieve_2.expected
        -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/sieve_2.actual
        -P ${CMAKE_CURRENT_SOURCE_DIR}/test.cmake
)

add_test(
    NAME sieve_test_3
    COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:lab1>
        -DMODE=sieve
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/sieve_3.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/sieve_3.expected
        -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/sieve_3.actual
        -P ${CMAKE_CURRENT_SOURCE_DIR}/test.cmake
)

add_test(
    NAME mindiff_test_1
    COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:lab1>
        -DMODE=mindiff
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/mindiff_1.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/mindiff_1.expected
        -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/mindiff_1.actual
        -P ${CMAKE_CURRENT_SOURCE_DIR}/test.cmake
)

add_test(
    NAME mindiff_test_2
    COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:lab1>
        -DMODE=mindiff
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/mindiff_2.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/mindiff_2.expected
        -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/mindiff_2.actual
        -P ${CMAKE_CURRENT_SOURCE_DIR}/test.cmake
)

add_test(
    NAME mindiff_test_3
    COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:lab1>
        -DMODE=mindiff
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/mindiff_3.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/mindiff_3.expected
        -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/mindiff_3.actual
        -P ${CMAKE_CURRENT_SOURCE_DIR}/test.cmake
)

