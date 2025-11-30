cmake_minimum_required(VERSION 3.10)
project(Lab3CPP)

set(CMAKE_CXX_STANDARD 11)

add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

# Тест с более гибким регулярным выражением
add_test(NAME TestLab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab3CPP PROPERTIES 
    PASS_REGULAR_EXPRESSION "0.*1.*2.*2"
)