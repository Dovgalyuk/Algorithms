cmake_minimum_required(VERSION 3.15)
project(ParallelResistance)

set(CMAKE_CXX_STANDARD 17)

add_executable(ParallelResistance main.cpp)

enable_testing()
add_test(NAME TestParallelResistance
         COMMAND ParallelResistance ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)