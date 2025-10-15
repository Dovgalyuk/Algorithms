# CMake generated Testfile for 
# Source directory: C:/Users/Vanek/source/repos/Algorithms3/Lab1C
# Build directory: C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab1C
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestLab1C "C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab1C/Lab1C.exe" "C:/Users/Vanek/source/repos/Algorithms3/Lab1C/input.txt")
set_tests_properties(TestLab1C PROPERTIES  PASS_REGULAR_EXPRESSION "Task1: element closest to average \\(2\\.50\\) is 2[
]*Task2: shifted array = 3 4 0 0" _BACKTRACE_TRIPLES "C:/Users/Vanek/source/repos/Algorithms3/Lab1C/CMakeLists.txt;4;add_test;C:/Users/Vanek/source/repos/Algorithms3/Lab1C/CMakeLists.txt;0;")
add_test(TestLab1C_2 "C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab1C/Lab1C.exe" "C:/Users/Vanek/source/repos/Algorithms3/Lab1C/input2.txt")
set_tests_properties(TestLab1C_2 PROPERTIES  PASS_REGULAR_EXPRESSION "Task1: element closest to average \\(30\\.00\\) is 30[
]*Task2: shifted array = 0 5" _BACKTRACE_TRIPLES "C:/Users/Vanek/source/repos/Algorithms3/Lab1C/CMakeLists.txt;7;add_test;C:/Users/Vanek/source/repos/Algorithms3/Lab1C/CMakeLists.txt;0;")
