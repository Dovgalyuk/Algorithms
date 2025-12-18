cmake_minimum_required(VERSION 3.10)
project(Lab3CPP)

set(CMAKE_CXX_STANDARD 11)

add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

# Тест с более гибким регулярным выражением
add_test(NAME TestLab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab3CPP PROPERTIES 
    PASS_REGULAR_EXPRESSION "4"
)

add_test(NAME TestLab3CPP1 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(TestLab3CPP1 PROPERTIES 
    PASS_REGULAR_EXPRESSION "1"
)

add_test(NAME TestLab3CPP2 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(TestLab3CPP2 PROPERTIES 
    PASS_REGULAR_EXPRESSION "5"
)

add_test(NAME TestLab3CPP3 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_tests_properties(TestLab3CPP3 PROPERTIES 
    PASS_REGULAR_EXPRESSION "3"
)

add_test(NAME TestLab3CPP4 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_tests_properties(TestLab3CPP4 PROPERTIES 
    PASS_REGULAR_EXPRESSION "0"
)

add_test(NAME TestLab3CPP5 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_tests_properties(TestLab3CPP5 PROPERTIES 
    PASS_REGULAR_EXPRESSION "2"
)