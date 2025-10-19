# CMake generated Testfile for 
# Source directory: C:/Users/Пользователь/source/repos/Algorithms/Lab1CPP
# Build directory: C:/Users/Пользователь/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestLab1CPPClass "C:/Users/Пользователь/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP/Lab1CPP.exe" "C:/Users/Пользователь/source/repos/Algorithms/Lab1CPP/input.txt")
set_tests_properties(TestLab1CPPClass PROPERTIES  PASS_REGULAR_EXPRESSION "Fibo numbers: 0 1 1 2 3 5 8 13 21 34.*Found: 9|Found: 9.*Fibo numbers: 0 1 1 2 3 5 8 13 21 34" _BACKTRACE_TRIPLES "C:/Users/Пользователь/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;5;add_test;C:/Users/Пользователь/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;0;")
add_test(TestCriticalData "C:/Users/Пользователь/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP/Lab1CPP.exe" "C:/Users/Пользователь/source/repos/Algorithms/Lab1CPP/tests/test_input_2.txt")
set_tests_properties(TestCriticalData PROPERTIES  PASS_REGULAR_EXPRESSION "Fibo numbers: 0.*The numbers were not found!|The numbers were not found!.*Fibo numbers: 0" _BACKTRACE_TRIPLES "C:/Users/Пользователь/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;9;add_test;C:/Users/Пользователь/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;0;")
add_test(TestDuplicatesOutput "C:/Users/Пользователь/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP/Lab1CPP.exe" "C:/Users/Пользователь/source/repos/Algorithms/Lab1CPP/tests/test_input_3.txt")
set_tests_properties(TestDuplicatesOutput PROPERTIES  PASS_REGULAR_EXPRESSION "Fibo numbers: 0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181 6765 10946 17711 28657 46368.*Found: 1.*Found: 2.*Found: 3.*Found: 4.*Found: 5.|Found: 1.*Found: 2.*Found: 3.*Found: 4.*Found: 5.*Fibo numbers: 0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181 6765 10946 17711 28657 46368" _BACKTRACE_TRIPLES "C:/Users/Пользователь/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;12;add_test;C:/Users/Пользователь/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;0;")
