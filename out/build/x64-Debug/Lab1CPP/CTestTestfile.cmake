# CMake generated Testfile for 
# Source directory: C:/Users/Admin/source/repos/Algorithms/Lab1CPP
# Build directory: C:/Users/Admin/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestLab1CPP "C:/Users/Admin/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP/Lab1CPP.exe" "C:/Users/Admin/source/repos/Algorithms/Lab1CPP/input.txt")
set_tests_properties(TestLab1CPP PROPERTIES  PASS_REGULAR_EXPRESSION "Elements less than average \\(3\\.00\\): 1 2[
]*Most frequent element: 2 \\(occurs 3 times\\)" _BACKTRACE_TRIPLES "C:/Users/Admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;4;add_test;C:/Users/Admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;0;")
add_test(TestLab1CPP_None "C:/Users/Admin/source/repos/Algorithms/out/build/x64-Debug/Lab1CPP/Lab1CPP.exe" "C:/Users/Admin/source/repos/Algorithms/Lab1CPP/inputNone.txt")
set_tests_properties(TestLab1CPP_None PROPERTIES  PASS_REGULAR_EXPRESSION "Elements less than average.*none.*Most frequent element:.*" _BACKTRACE_TRIPLES "C:/Users/Admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;7;add_test;C:/Users/Admin/source/repos/Algorithms/Lab1CPP/CMakeLists.txt;0;")
