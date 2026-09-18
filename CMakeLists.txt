cmake_minimum_required(VERSION 3.16)

project(LabDynamicArray LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(array_test test_dynamic_array.cpp)
add_executable(fastest fastest.cpp)
add_executable(max_five_sum max_five_sum.cpp)

enable_testing()

add_test(NAME DynamicArrayTest COMMAND array_test)

add_test(
    NAME FastestTest1
    COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:fastest>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/input/fastest_1.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/expected/fastest_1.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/check_output.cmake
)

add_test(
    NAME FastestTest2
    COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:fastest>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/input/fastest_2.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/expected/fastest_2.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/check_output.cmake
)

add_test(
    NAME FastestTest3
    COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:fastest>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/input/fastest_3.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/expected/fastest_3.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/check_output.cmake
)

add_test(
    NAME MaxFiveSumTest1
    COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:max_five_sum>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/input/sum_1.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/expected/sum_1.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/check_output.cmake
)

add_test(
    NAME MaxFiveSumTest2
    COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:max_five_sum>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/input/sum_2.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/expected/sum_2.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/check_output.cmake
)

add_test(
    NAME MaxFiveSumTest3
    COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:max_five_sum>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/input/sum_3.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/expected/sum_3.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/check_output.cmake
)
