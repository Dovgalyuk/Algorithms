cmake_minimum_required(VERSION 3.10)
project(Lab3CPP CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab3CPP task.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

enable_testing()

add_test(NAME Test1Lab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test1_lab3.txt)
set_property(TEST Test1Lab3CPP PROPERTY PASS_REGULAR_EXPRESSION "4")

add_test(NAME Test2Lab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test2_lab3.txt)
set_property(TEST Test2Lab3CPP PROPERTY PASS_REGULAR_EXPRESSION "4")

add_test(NAME Test3Lab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test3_lab3.txt)
set_property(TEST Test3Lab3CPP PROPERTY PASS_REGULAR_EXPRESSION "no reachable goal")

add_test(NAME Test4Lab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test4_lab3.txt)
set_property(TEST Test4Lab3CPP PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME Test5Lab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test5_lab3.txt)
set_property(TEST Test5Lab3CPP PROPERTY PASS_REGULAR_EXPRESSION "3")

add_test(NAME Test6Lab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test6_lab3.txt)
set_property(TEST Test6Lab3CPP PROPERTY WILL_FAIL TRUE)