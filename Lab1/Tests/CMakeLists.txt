cmake_minimum_required(VERSION 3.10)
project(ConsoleApplication2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ConsoleApplication2 ConsoleApplication2.cpp)

add_test(NAME TestConsoleApp COMMAND ConsoleApplication2 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestConsoleApp PROPERTY PASS_REGULAR_EXPRESSION ".*0.*1.*2.*3.*4.*5.*6.*7.*8.*9.*2.*")