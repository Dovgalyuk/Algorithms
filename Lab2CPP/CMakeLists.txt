add_executable(Beatnik beatnik.cpp)
target_include_directories(Beatnik PRIVATE ../LibraryCPP)
target_link_libraries(Beatnik PRIVATE LibraryCPP)

add_test(
    NAME TestBeatnikExample
    COMMAND Beatnik
        "${CMAKE_CURRENT_SOURCE_DIR}/script.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
)

set_tests_properties(TestBeatnikExample PROPERTIES
    PASS_REGULAR_EXPRESSION "^H[\r\n]*$"
    TIMEOUT 5
)

add_test(
    NAME TestBeatnikStack
    COMMAND Beatnik
        "${CMAKE_CURRENT_SOURCE_DIR}/stack_script.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
)

set_tests_properties(TestBeatnikStack PROPERTIES
    PASS_REGULAR_EXPRESSION "^AA[\r\n]*$"
    TIMEOUT 5
)

add_test(
    NAME TestBeatnikSubtract
    COMMAND Beatnik
        "${CMAKE_CURRENT_SOURCE_DIR}/subtract_script.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
)

set_tests_properties(TestBeatnikSubtract PROPERTIES
    PASS_REGULAR_EXPRESSION "^:[\r\n]*$"
    TIMEOUT 5
)

add_test(
    NAME TestBeatnikSwap
    COMMAND Beatnik
        "${CMAKE_CURRENT_SOURCE_DIR}/swap_script.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/two_letters.txt"
)

set_tests_properties(TestBeatnikSwap PROPERTIES
    PASS_REGULAR_EXPRESSION "^AB[\r\n]*$"
    TIMEOUT 5
)

add_test(
    NAME TestBeatnikForwardZero
    COMMAND Beatnik
        "${CMAKE_CURRENT_SOURCE_DIR}/forward_zero.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
)

set_tests_properties(TestBeatnikForwardZero PROPERTIES
    PASS_REGULAR_EXPRESSION "^A[\r\n]*$"
    TIMEOUT 5
)

add_test(
    NAME TestBeatnikForwardNonzero
    COMMAND Beatnik
        "${CMAKE_CURRENT_SOURCE_DIR}/forward_nonzero.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
)

set_tests_properties(TestBeatnikForwardNonzero PROPERTIES
    PASS_REGULAR_EXPRESSION "^A[\r\n]*$"
    TIMEOUT 5
)

add_test(
    NAME TestBeatnikLoop
    COMMAND Beatnik
        "${CMAKE_CURRENT_SOURCE_DIR}/loop_script.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/three_letters.txt"
)

set_tests_properties(TestBeatnikLoop PROPERTIES
    PASS_REGULAR_EXPRESSION "^ABC[\r\n]*$"
    TIMEOUT 5
)

add_test(
    NAME TestBeatnikBackwardZero
    COMMAND Beatnik
        "${CMAKE_CURRENT_SOURCE_DIR}/backward_zero.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
)

set_tests_properties(TestBeatnikBackwardZero PROPERTIES
    PASS_REGULAR_EXPRESSION "^A[\r\n]*$"
    TIMEOUT 5
)

add_test(
    NAME TestBeatnikPunctuation
    COMMAND Beatnik
        "${CMAKE_CURRENT_SOURCE_DIR}/punctuation_script.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
)

set_tests_properties(TestBeatnikPunctuation PROPERTIES
    PASS_REGULAR_EXPRESSION "^H[\r\n]*$"
    TIMEOUT 5
)
