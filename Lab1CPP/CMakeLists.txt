add_executable(Palindromes palindromes.cpp)
target_include_directories(Palindromes PRIVATE ../LibraryCPP)
target_link_libraries(Palindromes PRIVATE LibraryCPP)

add_test(
    NAME TestPalindromes12
    COMMAND Palindromes ${CMAKE_CURRENT_SOURCE_DIR}/palindromes_input.txt
)

set_tests_properties(TestPalindromes12 PROPERTIES
    PASS_REGULAR_EXPRESSION "^1 2 3 4 5 6 7 8 9 11 22 33[\r\n]*$"
)

add_test(
    NAME TestPalindromes1
    COMMAND Palindromes ${CMAKE_CURRENT_SOURCE_DIR}/tests/palindromes_1.txt
)

set_tests_properties(TestPalindromes1 PROPERTIES
    PASS_REGULAR_EXPRESSION "^1[\r\n]*$"
)

add_test(
    NAME TestPalindromes20
    COMMAND Palindromes ${CMAKE_CURRENT_SOURCE_DIR}/tests/palindromes_20.txt
)

set_tests_properties(TestPalindromes20 PROPERTIES
    PASS_REGULAR_EXPRESSION "^1 2 3 4 5 6 7 8 9 11 22 33 44 55 66 77 88 99 101 111[\r\n]*$"
)

add_executable(RLE rle.cpp)
target_include_directories(RLE PRIVATE ../LibraryCPP)
target_link_libraries(RLE PRIVATE LibraryCPP)

add_test(
    NAME TestRLEGroups
    COMMAND RLE ${CMAKE_CURRENT_SOURCE_DIR}/tests/rle_groups.txt
)
set_tests_properties(TestRLEGroups PROPERTIES
    PASS_REGULAR_EXPRESSION "^4 3[\r\n]+7 2[\r\n]+2 1[\r\n]+4 2[\r\n]*$"
)

add_test(
    NAME TestRLESame
    COMMAND RLE ${CMAKE_CURRENT_SOURCE_DIR}/tests/rle_same.txt
)
set_tests_properties(TestRLESame PROPERTIES
    PASS_REGULAR_EXPRESSION "^7 5[\r\n]*$"
)

add_test(
    NAME TestRLEDifferent
    COMMAND RLE ${CMAKE_CURRENT_SOURCE_DIR}/tests/rle_different.txt
)
set_tests_properties(TestRLEDifferent PROPERTIES
    PASS_REGULAR_EXPRESSION "^1 1[\r\n]+2 1[\r\n]+3 1[\r\n]+4 1[\r\n]*$"
)

add_test(
    NAME TestRLESingle
    COMMAND RLE ${CMAKE_CURRENT_SOURCE_DIR}/tests/rle_single.txt
)
set_tests_properties(TestRLESingle PROPERTIES
    PASS_REGULAR_EXPRESSION "^9 1[\r\n]*$"
)