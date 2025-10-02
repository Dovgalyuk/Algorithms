cmake_minimum_required(VERSION 3.10)
project(DOVprac1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DOVprac1 DOVprac1.cpp testARR.cpp)
target_include_directories(DOVprac1 PRIVATE .)

enable_testing()

set(SRC_DIR ${CMAKE_SOURCE_DIR})

file(COPY ${SRC_DIR}/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_test(
    NAME DOVprac1_test
    COMMAND sh -c "$<TARGET_FILE:DOVprac1> && diff ${SRC_DIR}/expected.txt output.txt"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)