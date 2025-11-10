# CMake generated Testfile for 
# Source directory: C:/Users/badvo/OneDrive/Документы/GitHub/Algorithms/Lab1Cpp
# Build directory: C:/Users/badvo/OneDrive/Документы/GitHub/Algorithms/Lab1Cpp/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestLab1_Simples "C:/Users/badvo/OneDrive/Документы/GitHub/Algorithms/Lab1Cpp/build/Lab1Cpp.exe" "1")
set_tests_properties(TestLab1_Simples PROPERTIES  PASS_REGULAR_EXPRESSION "Simple: 2 3 5 7 11" WORKING_DIRECTORY "C:/Users/badvo/OneDrive/Документы/GitHub/Algorithms/Lab1Cpp" _BACKTRACE_TRIPLES "C:/Users/badvo/OneDrive/Документы/GitHub/Algorithms/Lab1Cpp/CMakeLists.txt;16;add_test;C:/Users/badvo/OneDrive/Документы/GitHub/Algorithms/Lab1Cpp/CMakeLists.txt;0;")
add_test(TestLab1_Shift "C:/Users/badvo/OneDrive/Документы/GitHub/Algorithms/Lab1Cpp/build/Lab1Cpp.exe" "2")
set_tests_properties(TestLab1_Shift PROPERTIES  PASS_REGULAR_EXPRESSION "shift: 0 0 10 20 30 40" WORKING_DIRECTORY "C:/Users/badvo/OneDrive/Документы/GitHub/Algorithms/Lab1Cpp" _BACKTRACE_TRIPLES "C:/Users/badvo/OneDrive/Документы/GitHub/Algorithms/Lab1Cpp/CMakeLists.txt;22;add_test;C:/Users/badvo/OneDrive/Документы/GitHub/Algorithms/Lab1Cpp/CMakeLists.txt;0;")
