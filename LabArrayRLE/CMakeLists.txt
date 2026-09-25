add_executable(LabArrayRLE main.cpp)

target_include_directories(LabArrayRLE PRIVATE
    ../LibraryCPPClass
)

target_link_libraries(LabArrayRLE PRIVATE
    LibraryCPPClass
)

add_test(
    NAME RLE1
    COMMAND LabArrayRLE ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
)

set_tests_properties(
    RLE1
    PROPERTIES
    PASS_REGULAR_EXPRESSION "1 4 2 2 3 3 5 1"
)

add_test(
    NAME RLE2
    COMMAND LabArrayRLE ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
)

set_tests_properties(
    RLE2
    PROPERTIES
    PASS_REGULAR_EXPRESSION "1 1 2 1 3 1 4 1 5 1"
)

add_test(
    NAME RLE3
    COMMAND LabArrayRLE ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt
)

set_tests_properties(
    RLE3
    PROPERTIES
    PASS_REGULAR_EXPRESSION "7 8"
)

add_test(
    NAME RLE4
    COMMAND LabArrayRLE ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt
)

set_tests_properties(
    RLE4
    PROPERTIES
    PASS_REGULAR_EXPRESSION "0 2 -1 3 5 2 0 3"
)