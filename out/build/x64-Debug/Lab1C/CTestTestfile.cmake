# CMake generated Testfile for 
# Source directory: C:/Algorithms/Lab1C
# Build directory: C:/Algorithms/out/build/x64-Debug/Lab1C
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Test1 "C:/Algorithms/out/build/x64-Debug/Lab1C/Lab1C.exe" "C:/Algorithms/Lab1C/input1.txt")
set_tests_properties(Test1 PROPERTIES  PASS_REGULAR_EXPRESSION "5\\.454545.*\\(1,2\\) \\(2,1\\) \\(3,1\\)" _BACKTRACE_TRIPLES "C:/Algorithms/Lab1C/CMakeLists.txt;5;add_test;C:/Algorithms/Lab1C/CMakeLists.txt;0;")
add_test(Test2 "C:/Algorithms/out/build/x64-Debug/Lab1C/Lab1C.exe" "C:/Algorithms/Lab1C/input2.txt")
set_tests_properties(Test2 PROPERTIES  PASS_REGULAR_EXPRESSION "3\\.333333.*\\(7,5\\)" _BACKTRACE_TRIPLES "C:/Algorithms/Lab1C/CMakeLists.txt;8;add_test;C:/Algorithms/Lab1C/CMakeLists.txt;0;")
