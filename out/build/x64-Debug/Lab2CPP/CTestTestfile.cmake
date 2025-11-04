# CMake generated Testfile for 
# Source directory: C:/Users/Admin/source/repos/Algorithms/Lab2CPP
# Build directory: C:/Users/Admin/source/repos/Algorithms/out/build/x64-Debug/Lab2CPP
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestLab2CPP_1 "C:/Users/Admin/source/repos/Algorithms/out/build/x64-Debug/Lab2CPP/Lab2CPP.exe" "C:/Users/Admin/source/repos/Algorithms/Lab2CPP/input1.txt")
set_tests_properties(TestLab2CPP_1 PROPERTIES  PASS_REGULAR_EXPRESSION "Result: 6" _BACKTRACE_TRIPLES "C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;6;add_test;C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;0;")
add_test(TestLab2CPP_2 "C:/Users/Admin/source/repos/Algorithms/out/build/x64-Debug/Lab2CPP/Lab2CPP.exe" "C:/Users/Admin/source/repos/Algorithms/Lab2CPP/input2.txt")
set_tests_properties(TestLab2CPP_2 PROPERTIES  PASS_REGULAR_EXPRESSION "Result: 5" _BACKTRACE_TRIPLES "C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;9;add_test;C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;0;")
add_test(TestLab2CPP_3 "C:/Users/Admin/source/repos/Algorithms/out/build/x64-Debug/Lab2CPP/Lab2CPP.exe" "C:/Users/Admin/source/repos/Algorithms/Lab2CPP/input3.txt")
set_tests_properties(TestLab2CPP_3 PROPERTIES  PASS_REGULAR_EXPRESSION "Result: 9" _BACKTRACE_TRIPLES "C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;12;add_test;C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;0;")
add_test(TestLab2CPP_4 "C:/Users/Admin/source/repos/Algorithms/out/build/x64-Debug/Lab2CPP/Lab2CPP.exe" "C:/Users/Admin/source/repos/Algorithms/Lab2CPP/input4.txt")
set_tests_properties(TestLab2CPP_4 PROPERTIES  PASS_REGULAR_EXPRESSION "Result: 16" _BACKTRACE_TRIPLES "C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;15;add_test;C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;0;")
add_test(TestLab2CPP_5 "C:/Users/Admin/source/repos/Algorithms/out/build/x64-Debug/Lab2CPP/Lab2CPP.exe" "C:/Users/Admin/source/repos/Algorithms/Lab2CPP/input5.txt")
set_tests_properties(TestLab2CPP_5 PROPERTIES  PASS_REGULAR_EXPRESSION "Result: 28" _BACKTRACE_TRIPLES "C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;18;add_test;C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;0;")
add_test(TestLab2CPP_6 "C:/Users/Admin/source/repos/Algorithms/out/build/x64-Debug/Lab2CPP/Lab2CPP.exe" "C:/Users/Admin/source/repos/Algorithms/Lab2CPP/input6.txt")
set_tests_properties(TestLab2CPP_6 PROPERTIES  PASS_REGULAR_EXPRESSION "Result: 19" _BACKTRACE_TRIPLES "C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;21;add_test;C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;0;")
add_test(TestLab2CPP_Error_DivZero "C:/Users/Admin/source/repos/Algorithms/out/build/x64-Debug/Lab2CPP/Lab2CPP.exe" "input_error1.txt")
set_tests_properties(TestLab2CPP_Error_DivZero PROPERTIES  PASS_REGULAR_EXPRESSION "Error: Division by zero" WORKING_DIRECTORY "C:/Users/Admin/source/repos/Algorithms/Lab2CPP" _BACKTRACE_TRIPLES "C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;24;add_test;C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;0;")
add_test(TestLab2CPP_Error_ParenOpen "C:/Users/Admin/source/repos/Algorithms/out/build/x64-Debug/Lab2CPP/Lab2CPP.exe" "input_error2.txt")
set_tests_properties(TestLab2CPP_Error_ParenOpen PROPERTIES  PASS_REGULAR_EXPRESSION "Error: Mismatched parentheses" WORKING_DIRECTORY "C:/Users/Admin/source/repos/Algorithms/Lab2CPP" _BACKTRACE_TRIPLES "C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;27;add_test;C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;0;")
add_test(TestLab2CPP_Error_InvalidExpr "C:/Users/Admin/source/repos/Algorithms/out/build/x64-Debug/Lab2CPP/Lab2CPP.exe" "input_error3.txt")
set_tests_properties(TestLab2CPP_Error_InvalidExpr PROPERTIES  PASS_REGULAR_EXPRESSION "Error: Invalid expression" WORKING_DIRECTORY "C:/Users/Admin/source/repos/Algorithms/Lab2CPP" _BACKTRACE_TRIPLES "C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;30;add_test;C:/Users/Admin/source/repos/Algorithms/Lab2CPP/CMakeLists.txt;0;")
