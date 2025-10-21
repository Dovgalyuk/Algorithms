add_executable(Lab1C lab1.c)
target_include_directories(Lab1C PUBLIC ../LibraryC)
target_link_libraries(Lab1C LibraryC)

add_test(NAME TestPrimeNumbers COMMAND Lab1C input.txt)
set_property(TEST TestPrimeNumbers PROPERTY PASS_REGULAR_EXPRESSION "2 3 5 7 11 13 17 19 23 29")

add_test(NAME TestEvenDifference COMMAND Lab1C input.txt)
set_property(TEST TestEvenDifference PROPERTY PASS_REGULAR_EXPRESSION "the minimum difference between two even elements: 2")