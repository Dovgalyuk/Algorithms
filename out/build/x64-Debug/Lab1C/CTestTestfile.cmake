# CMake generated Testfile for 
# Source directory: C:/Users/Кирилл/source/repos/Algorithms/Lab1C
# Build directory: C:/Users/Кирилл/source/repos/Algorithms/out/build/x64-Debug/Lab1C
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestLab1_Task1 "C:/Users/Кирилл/source/repos/Algorithms/out/build/x64-Debug/Lab1C/Lab1C.exe" "C:/Users/Кирилл/source/repos/Algorithms/Lab1C/input.txt" "task1")
set_tests_properties(TestLab1_Task1 PROPERTIES  PASS_REGULAR_EXPRESSION "496 1215 2384 3165 4216 5055 6135 7225 8255 9285 10264 11235" _BACKTRACE_TRIPLES "C:/Users/Кирилл/source/repos/Algorithms/Lab1C/CMakeLists.txt;5;add_test;C:/Users/Кирилл/source/repos/Algorithms/Lab1C/CMakeLists.txt;0;")
add_test(TestLab1_Task2 "C:/Users/Кирилл/source/repos/Algorithms/out/build/x64-Debug/Lab1C/Lab1C.exe" "C:/Users/Кирилл/source/repos/Algorithms/Lab1C/input.txt" "task2")
set_tests_properties(TestLab1_Task2 PROPERTIES  PASS_REGULAR_EXPRESSION "1 6 7 8 9 .* 0 0 0 0" _BACKTRACE_TRIPLES "C:/Users/Кирилл/source/repos/Algorithms/Lab1C/CMakeLists.txt;10;add_test;C:/Users/Кирилл/source/repos/Algorithms/Lab1C/CMakeLists.txt;0;")
