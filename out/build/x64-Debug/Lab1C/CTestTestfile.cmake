# CMake generated Testfile for 
# Source directory: C:/Users/dimas/source/repos/Algorithms/Lab1C
# Build directory: C:/Users/dimas/source/repos/Algorithms/out/build/x64-Debug/Lab1C
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestFibonachi "C:/Users/dimas/source/repos/Algorithms/out/build/x64-Debug/Lab1C/Lab1CPP.exe" "C:/Users/dimas/source/repos/Algorithms/Lab1C/input1.txt")
set_tests_properties(TestFibonachi PROPERTIES  PASS_REGULAR_EXPRESSION "0 1 1 2 3 5 8 13 21 34" _BACKTRACE_TRIPLES "C:/Users/dimas/source/repos/Algorithms/Lab1C/CMakeLists.txt;6;add_test;C:/Users/dimas/source/repos/Algorithms/Lab1C/CMakeLists.txt;0;")
add_test(TestCompressed "C:/Users/dimas/source/repos/Algorithms/out/build/x64-Debug/Lab1C/Lab1CPP.exe" "C:/Users/dimas/source/repos/Algorithms/Lab1C/input2.txt")
set_tests_properties(TestCompressed PROPERTIES  PASS_REGULAR_EXPRESSION "20 3 25 0 0 0 0 0" _BACKTRACE_TRIPLES "C:/Users/dimas/source/repos/Algorithms/Lab1C/CMakeLists.txt;10;add_test;C:/Users/dimas/source/repos/Algorithms/Lab1C/CMakeLists.txt;0;")
