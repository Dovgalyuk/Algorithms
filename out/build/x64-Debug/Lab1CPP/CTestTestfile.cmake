# CMake generated Testfile for 
# Source directory: C:/Users/marui/source/repos/Algorithms/Lab1CPP
# Build directory: C:/Users/marui/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestLab1CPP "C:/Users/marui/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP/Lab1CPP.exe" "C:/Users/marui/source/repos/Algorithms/Lab1CPP/input.txt")
set_tests_properties(TestLab1CPP PROPERTIES  PASS_REGULAR_EXPRESSION "Factorial: 1 1 2 6 24 120 720 5040 40320 362880(.||
)*Maximum sum: 35(.||
)*Elements with maximum sum: 5 6 7 8 9" _BACKTRACE_TRIPLES "C:/Users/marui/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;4;add_test;C:/Users/marui/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;0;")
