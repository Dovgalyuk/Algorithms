cmake_minimum_required(VERSION 3.10)
project(LabCPP2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LabCPP2 lab2.cpp)
target_include_directories(LabCPP2 PRIVATE ../LibraryCPPClass)
target_link_libraries(LabCPP2 PRIVATE LibraryCPPClass)

enable_testing()

add_test(NAME TestMinipig_01_Example
    COMMAND LabCPP2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1s.txt)
set_property(TEST TestMinipig_01_Example
    PROPERTY PASS_REGULAR_EXPRESSION "^1 1[\r\n]+1 1 1")

add_test(NAME TestMinipig_02_InputOutput
    COMMAND LabCPP2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2s.txt
                    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2i.txt)
set_property(TEST TestMinipig_02_InputOutput
    PROPERTY PASS_REGULAR_EXPRESSION "^42[\r\n]+1")

add_test(NAME TestMinipig_03_Sub
    COMMAND LabCPP2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3s.txt
                    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3i.txt)
set_property(TEST TestMinipig_03_Sub
    PROPERTY PASS_REGULAR_EXPRESSION "^2")

add_test(NAME TestMinipig_04_Switch
    COMMAND LabCPP2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test4s.txt
                    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test4i.txt)
set_property(TEST TestMinipig_04_Switch
    PROPERTY PASS_REGULAR_EXPRESSION "^3 2 1")

add_test(NAME TestMinipig_05_Char
    COMMAND LabCPP2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test5s.txt
                    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test5i.txt)
set_property(TEST TestMinipig_05_Char
    PROPERTY PASS_REGULAR_EXPRESSION "^A[\r\n]+1")

add_test(NAME TestMinipig_06_TwoOutputs
    COMMAND LabCPP2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test6s.txt
                    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test6i.txt)
set_property(TEST TestMinipig_06_TwoOutputs
    PROPERTY PASS_REGULAR_EXPRESSION "^1020[\r\n]+1 1")

add_test(NAME TestMinipig_07_Mixed
    COMMAND LabCPP2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test7s.txt
                    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test7i.txt)
set_property(TEST TestMinipig_07_Mixed
    PROPERTY PASS_REGULAR_EXPRESSION "^7B[\r\n]+1 1")

add_test(NAME TestMinipig_08_ManyInputs
    COMMAND LabCPP2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test8s.txt
                    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test8i.txt)
set_property(TEST TestMinipig_08_ManyInputs
    PROPERTY PASS_REGULAR_EXPRESSION "5 3 42 -1 100")