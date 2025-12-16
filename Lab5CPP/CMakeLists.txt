cmake_minimum_required(VERSION 3.10)
project(Lab5CPP)

add_executable(Lab5CPP
    lab5.cpp
    ../LibraryCPP/avltree.cpp
)

target_include_directories(Lab5CPP PUBLIC ../LibraryCPP)

enable_testing()

add_test(NAME BasicFunctionalityTest
    COMMAND Lab5CPP 1
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_test(NAME StressTest
    COMMAND Lab5CPP 2
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_test(NAME ComparisonTest
    COMMAND Lab5CPP 4
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_test(NAME FileInputTest
    COMMAND Lab5CPP 6
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)