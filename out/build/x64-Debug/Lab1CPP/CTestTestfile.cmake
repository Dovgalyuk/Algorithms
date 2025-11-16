# CMake generated Testfile for 
# Source directory: C:/Users/Momoe/Desktop/labD/2/Algorithms/Lab1CPP
# Build directory: C:/Users/Momoe/Desktop/labD/2/Algorithms/out/build/x64-Debug/Lab1CPP
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestLab1CPP "C:/Users/Momoe/Desktop/labD/2/Algorithms/out/build/x64-Debug/Lab1CPP/Lab1CPP.exe" "C:/Users/Momoe/Desktop/labD/2/Algorithms/Lab1CPP/input.txt")
set_tests_properties(TestLab1CPP PROPERTIES  PASS_REGULAR_EXPRESSION "5,0 1 2 3 4 " _BACKTRACE_TRIPLES "C:/Users/Momoe/Desktop/labD/2/Algorithms/Lab1CPP/CMakeLists.txt;5;add_test;C:/Users/Momoe/Desktop/labD/2/Algorithms/Lab1CPP/CMakeLists.txt;0;")
add_test(TestLab1CPP2 "C:/Users/Momoe/Desktop/labD/2/Algorithms/out/build/x64-Debug/Lab1CPP/Lab1CPP.exe" "C:/Users/Momoe/Desktop/labD/2/Algorithms/Lab1CPP/input2.txt")
set_tests_properties(TestLab1CPP2 PROPERTIES  PASS_REGULAR_EXPRESSION "0,0 " _BACKTRACE_TRIPLES "C:/Users/Momoe/Desktop/labD/2/Algorithms/Lab1CPP/CMakeLists.txt;8;add_test;C:/Users/Momoe/Desktop/labD/2/Algorithms/Lab1CPP/CMakeLists.txt;0;")
