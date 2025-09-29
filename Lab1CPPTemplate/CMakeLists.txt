add_executable(Palindrome palindrome.cpp)
add_executable(Compressor compressor.cpp)

target_include_directories(Palindrome PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Palindrome LibraryCPPTemplate)

target_include_directories(Compressor PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Compressor LibraryCPPTemplate)

add_test(NAME TestPalindrome COMMAND Palindrome ${CMAKE_CURRENT_SOURCE_DIR}/palindroms.txt)
set_property(TEST TestPalindrome PROPERTY PASS_REGULAR_EXPRESSION "1 2 3 4 5 6 7 8 9 11 22 33 44 55 66")

add_test(NAME TestCompressor COMMAND Compressor ${CMAKE_CURRENT_SOURCE_DIR}/compressor.txt)
set_property(TEST TestCompressor PROPERTY PASS_REGULAR_EXPRESSION "1 5 7 30 35 40 0 0 0 0")
