cmake_minimum_required(VERSION 3.10)
project(Lab3CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../LibraryCPP/Tests ${CMAKE_BINARY_DIR}/LibraryCPP_Tests)

add_executable(conapp main.cpp)
target_include_directories(conapp PUBLIC ../LibraryCPP)
target_link_libraries(conapp PRIVATE LibraryCPP)

#enable_testing()
#
#add_test(NAME script1_hello
#    COMMAND script
#        ${CMAKE_CURRENT_SOURCE_DIR}/script1.txt
#        ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
#)
#set_property(TEST script1_hello PROPERTY
#    PASS_REGULAR_EXPRESSION "Hello, World!")
