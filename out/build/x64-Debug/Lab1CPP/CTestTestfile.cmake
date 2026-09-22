# CMake generated Testfile for 
# Source directory: C:/Users/admin/source/repos/Algorithms/Lab1CPP
# Build directory: C:/Users/admin/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestSieveByInput1 "C:/Users/admin/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP/SieveOfEratosthenes.exe" "C:/Users/admin/source/repos/Algorithms/Lab1CPP/SieveTestData/input1.txt")
set_tests_properties(TestSieveByInput1 PROPERTIES  PASS_REGULAR_EXPRESSION "2 3 5 7 11 13 17 19 0 0 0 0 0 0 0 0 0 0 0 0" _BACKTRACE_TRIPLES "C:/Users/admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;7;add_test;C:/Users/admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;0;")
add_test(TestSieveByInput2 "C:/Users/admin/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP/SieveOfEratosthenes.exe" "C:/Users/admin/source/repos/Algorithms/Lab1CPP/SieveTestData/input2.txt")
set_tests_properties(TestSieveByInput2 PROPERTIES  PASS_REGULAR_EXPRESSION "2 0" _BACKTRACE_TRIPLES "C:/Users/admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;10;add_test;C:/Users/admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;0;")
add_test(TestSieveByInput3 "C:/Users/admin/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP/SieveOfEratosthenes.exe" "C:/Users/admin/source/repos/Algorithms/Lab1CPP/SieveTestData/input3.txt")
set_tests_properties(TestSieveByInput3 PROPERTIES  PASS_REGULAR_EXPRESSION "" _BACKTRACE_TRIPLES "C:/Users/admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;13;add_test;C:/Users/admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;0;")
add_test(TestNonDivisibleByInput1 "C:/Users/admin/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP/NonDivisible.exe" "C:/Users/admin/source/repos/Algorithms/Lab1CPP/NonDivisibleTestData/input1.txt")
set_tests_properties(TestNonDivisibleByInput1 PROPERTIES  PASS_REGULAR_EXPRESSION "2 3 5 7" _BACKTRACE_TRIPLES "C:/Users/admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;16;add_test;C:/Users/admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;0;")
add_test(TestNonDivisibleByInput2 "C:/Users/admin/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP/NonDivisible.exe" "C:/Users/admin/source/repos/Algorithms/Lab1CPP/NonDivisibleTestData/input2.txt")
set_tests_properties(TestNonDivisibleByInput2 PROPERTIES  PASS_REGULAR_EXPRESSION "5" _BACKTRACE_TRIPLES "C:/Users/admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;19;add_test;C:/Users/admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;0;")
add_test(TestNonDivisibleByInput3 "C:/Users/admin/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP/NonDivisible.exe" "C:/Users/admin/source/repos/Algorithms/Lab1CPP/NonDivisibleTestData/input3.txt")
set_tests_properties(TestNonDivisibleByInput3 PROPERTIES  PASS_REGULAR_EXPRESSION "1" _BACKTRACE_TRIPLES "C:/Users/admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;22;add_test;C:/Users/admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;0;")
