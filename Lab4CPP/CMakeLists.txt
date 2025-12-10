add_executable(Lab4CPP main.cpp)

target_include_directories(Lab4CPP PUBLIC
    ${CMAKE_SOURCE_DIR}/LibraryCPPTemplate)

add_test(NAME floyd_example
    COMMAND Lab4CPP "${CMAKE_SOURCE_DIR}/Lab4CPP/input.txt")

set_tests_properties(floyd_example PROPERTIES
    PASS_REGULAR_EXPRESSION "A -> D: A B C D \\(12\\)")
