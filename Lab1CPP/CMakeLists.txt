cmake_minimum_required(VERSION 3.10)
project(ArrayProcessing)

set(CMAKE_CXX_STANDARD 14)

add_executable(ArrayProcessing main.cpp array.h)

enable_testing()

add_test(ArrayProcessingTest ArrayProcessing)
set_property(TEST ArrayProcessingTest PROPERTY ENVIRONMENT "INPUT_FILE=input.txt")
