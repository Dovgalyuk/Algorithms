cmake_minimum_required(VERSION 3.15)
project(Lab4CPP LANGUAGES CXX)

add_executable(Lab4_FordFulkerson ford_fulkerson.cpp)
target_include_directories(Lab4_FordFulkerson PUBLIC ../LibraryCPPTemplate)

enable_testing()

add_test(NAME MaxFlowTest1 COMMAND Lab4_FordFulkerson "${CMAKE_CURRENT_SOURCE_DIR}/input1.txt")
set_property(TEST MaxFlowTest1 PROPERTY PASS_REGULAR_EXPRESSION "15")

add_test(NAME MaxFlowTest2 COMMAND Lab4_FordFulkerson "${CMAKE_CURRENT_SOURCE_DIR}/input2.txt")
set_property(TEST MaxFlowTest2 PROPERTY PASS_REGULAR_EXPRESSION "23")

add_test(NAME MaxFlowTest3 COMMAND Lab4_FordFulkerson "${CMAKE_CURRENT_SOURCE_DIR}/input3.txt")
set_property(TEST MaxFlowTest3 PROPERTY PASS_REGULAR_EXPRESSION "0")
