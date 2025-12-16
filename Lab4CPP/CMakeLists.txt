cmake_minimum_required(VERSION 3.15)
project(Lab4CPPProject LANGUAGES CXX)

enable_testing()

add_executable(Lab4CPP
    main.cpp
)

target_include_directories(Lab4CPP PRIVATE
    ${CMAKE_SOURCE_DIR}/LibraryCPPTemplate
)

set_target_properties(Lab4CPP PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

if (MSVC)
    target_compile_options(Lab4CPP PRIVATE /W4)
else()
    target_compile_options(Lab4CPP PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(
    NAME dijkstra_example
    COMMAND $<TARGET_FILE:Lab4CPP> "${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
)

set_tests_properties(dijkstra_example PROPERTIES
    PASS_REGULAR_EXPRESSION "Distance: 6\\.000000[ \t\r\n]*Path: A C D E"
)
