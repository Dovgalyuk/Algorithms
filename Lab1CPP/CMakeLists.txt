add_executable(Lab1CPP lab1.cpp )
target_include_directories(Lab1CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPP LibraryCPPClass)

add_test(NAME TestLab1CPPClass COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPPClass PROPERTY PASS_REGULAR_EXPRESSION "Fibo numbers: 0 1 1 2 3 5 8 13 21 34.*Found: 9|Found: 9.*Fibo numbers: 0 1 1 2 3 5 8 13 21 34")


add_test(NAME TestCriticalData COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_input_2.txt)
set_property(TEST TestCriticalData PROPERTY PASS_REGULAR_EXPRESSION "Fibo numbers: 0.*The numbers were not found!|The numbers were not found!.*Fibo numbers: 0")

add_test(NAME TestDuplicatesOutput COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_input_3.txt)
set_property(TEST TestDuplicatesOutput PROPERTY PASS_REGULAR_EXPRESSION "Fibo numbers: 0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181 6765 10946 17711 28657 46368.*Found: 1.*Found: 2.*Found: 3.*Found: 4.*Found: 5.|Found: 1.*Found: 2.*Found: 3.*Found: 4.*Found: 5.*Fibo numbers: 0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181 6765 10946 17711 28657 46368")
