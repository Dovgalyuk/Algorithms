# CMake generated Testfile for 
# Source directory: D:/Profiles/Acer/Desktop/Algorithms/Lab1CPP
# Build directory: D:/Profiles/Acer/Desktop/Algorithms/out/build/x64-Debug/Lab1CPP
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestLab1CPP "D:/Profiles/Acer/Desktop/Algorithms/out/build/x64-Debug/Lab1CPP/Lab1CPP.exe" "D:/Profiles/Acer/Desktop/Algorithms/Lab1CPP/input.txt")
set_tests_properties(TestLab1CPP PROPERTIES  PASS_REGULAR_EXPRESSION "B -> C : 2(.|
)*D -> A : NO PATH(.|
)*D -> D : 0" _BACKTRACE_TRIPLES "D:/Profiles/Acer/Desktop/Algorithms/Lab1CPP/CMakeLists.txt;5;add_test;D:/Profiles/Acer/Desktop/Algorithms/Lab1CPP/CMakeLists.txt;0;")
