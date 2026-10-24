add_executable(Lab1OddRun odd_run.cpp)
target_include_directories(Lab1OddRun PUBLIC ../LibraryCPPTemplate)

add_executable(Lab1RLE rle.cpp)
target_include_directories(Lab1RLE PUBLIC ../LibraryCPPTemplate)

add_test(
    NAME TestLab1OddRun1
    COMMAND Lab1OddRun ${CMAKE_CURRENT_SOURCE_DIR}/odd_input_1.txt
)

set_property(
    TEST TestLab1OddRun1
    PROPERTY PASS_REGULAR_EXPRESSION "4"
)

add_test(
    NAME TestLab1OddRun2
    COMMAND Lab1OddRun ${CMAKE_CURRENT_SOURCE_DIR}/odd_input_2.txt
)

set_property(
    TEST TestLab1OddRun2
    PROPERTY PASS_REGULAR_EXPRESSION "0"
)

add_test(
    NAME TestLab1RLE1
    COMMAND Lab1RLE ${CMAKE_CURRENT_SOURCE_DIR}/rle_input_1.txt
)

set_property(
    TEST TestLab1RLE1
    PROPERTY PASS_REGULAR_EXPRESSION "3 1[\r\n]+2 2[\r\n]+4 5"
)

add_test(
    NAME TestLab1RLE2
    COMMAND Lab1RLE ${CMAKE_CURRENT_SOURCE_DIR}/rle_input_2.txt
)

set_property(
    TEST TestLab1RLE2
    PROPERTY PASS_REGULAR_EXPRESSION "2 7[\r\n]+4 3[\r\n]+1 8[\r\n]+2 9[\r\n]+1 1"
)
