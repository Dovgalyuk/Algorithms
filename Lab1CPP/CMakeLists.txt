add_executable(SieveOfEratosthenes sieve_of_eratosthenes.cpp)
add_executable(NonDivisible non_divisible_elements.cpp)

target_include_directories(SieveOfEratosthenes PUBLIC ../LibraryCPPTemplate)
target_include_directories(NonDivisible PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestSieveByInput1 COMMAND SieveOfEratosthenes ${CMAKE_CURRENT_SOURCE_DIR}/SieveTestData/input1.txt)
set_property(TEST TestSieveByInput1 PROPERTY PASS_REGULAR_EXPRESSION "2 3 5 7 11 13 17 19 0 0 0 0 0 0 0 0 0 0 0 0")

add_test(NAME TestSieveByInput2 COMMAND SieveOfEratosthenes ${CMAKE_CURRENT_SOURCE_DIR}/SieveTestData/input2.txt)
set_property(TEST TestSieveByInput2 PROPERTY PASS_REGULAR_EXPRESSION "2 0")

add_test(NAME TestSieveByInput3 COMMAND SieveOfEratosthenes ${CMAKE_CURRENT_SOURCE_DIR}/SieveTestData/input3.txt)
set_property(TEST TestSieveByInput3 PROPERTY PASS_REGULAR_EXPRESSION "")

add_test(NAME TestNonDivisibleByInput1 COMMAND NonDivisible ${CMAKE_CURRENT_SOURCE_DIR}/NonDivisibleTestData/input1.txt)
set_property(TEST TestNonDivisibleByInput1 PROPERTY PASS_REGULAR_EXPRESSION "2 3 5 7")

add_test(NAME TestNonDivisibleByInput2 COMMAND NonDivisible ${CMAKE_CURRENT_SOURCE_DIR}/NonDivisibleTestData/input2.txt)
set_property(TEST TestNonDivisibleByInput2 PROPERTY PASS_REGULAR_EXPRESSION "5")

add_test(NAME TestNonDivisibleByInput3 COMMAND NonDivisible ${CMAKE_CURRENT_SOURCE_DIR}/NonDivisibleTestData/input3.txt)
set_property(TEST TestNonDivisibleByInput3 PROPERTY PASS_REGULAR_EXPRESSION "1")