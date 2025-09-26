cmake_minimum_required(VERSION 3.10)

add_executable(Lab1CPP main.cpp)

target_include_directories(Lab1CPP PUBLIC
    ${CMAKE_SOURCE_DIR}/LibraryCPPClass
)

target_link_libraries(Lab1CPP LibraryCPPClass)

enable_testing()

add_test(NAME TestLab1CPP
         COMMAND Lab1CPP "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")

set_tests_properties(TestLab1CPP PROPERTIES
  PASS_REGULAR_EXPRESSION "Sum of digits: 17;Most frequent: 2")

add_test(NAME TestLab1CPP_2
         COMMAND Lab1CPP "${CMAKE_CURRENT_SOURCE_DIR}/input_2.txt")

set_tests_properties(TestLab1CPP_2 PROPERTIES
  PASS_REGULAR_EXPRESSION "Sum of digits: 26;Most frequent: 5")
