# CMake generated Testfile for 
# Source directory: C:/Users/Vanek/source/repos/Algorithms3/Lab2CPP
# Build directory: C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab2CPP
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Lab2_Test1_BasicNumbers "C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab2CPP/Lab2CPP.exe" "C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab2CPP/tests/test1.txt")
set_tests_properties(Lab2_Test1_BasicNumbers PROPERTIES  PASS_REGULAR_EXPRESSION "3.*2.*1" _BACKTRACE_TRIPLES "C:/Users/Vanek/source/repos/Algorithms3/Lab2CPP/CMakeLists.txt;7;add_test;C:/Users/Vanek/source/repos/Algorithms3/Lab2CPP/CMakeLists.txt;0;")
add_test(Lab2_Test2_Arithmetic "C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab2CPP/Lab2CPP.exe" "C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab2CPP/tests/test2.txt")
set_tests_properties(Lab2_Test2_Arithmetic PROPERTIES  PASS_REGULAR_EXPRESSION "1.*2.*3.*6" _BACKTRACE_TRIPLES "C:/Users/Vanek/source/repos/Algorithms3/Lab2CPP/CMakeLists.txt;11;add_test;C:/Users/Vanek/source/repos/Algorithms3/Lab2CPP/CMakeLists.txt;0;")
add_test(Lab2_Test3_Multiplication "C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab2CPP/Lab2CPP.exe" "C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab2CPP/tests/test3.txt")
set_tests_properties(Lab2_Test3_Multiplication PROPERTIES  PASS_REGULAR_EXPRESSION "10" _BACKTRACE_TRIPLES "C:/Users/Vanek/source/repos/Algorithms3/Lab2CPP/CMakeLists.txt;14;add_test;C:/Users/Vanek/source/repos/Algorithms3/Lab2CPP/CMakeLists.txt;0;")
add_test(Lab2_Test4_Subtraction "C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab2CPP/Lab2CPP.exe" "C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab2CPP/tests/test4.txt")
set_tests_properties(Lab2_Test4_Subtraction PROPERTIES  PASS_REGULAR_EXPRESSION "8" _BACKTRACE_TRIPLES "C:/Users/Vanek/source/repos/Algorithms3/Lab2CPP/CMakeLists.txt;18;add_test;C:/Users/Vanek/source/repos/Algorithms3/Lab2CPP/CMakeLists.txt;0;")
add_test(Lab2_Test5_Logical "C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab2CPP/Lab2CPP.exe" "C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab2CPP/tests/test5.txt")
set_tests_properties(Lab2_Test5_Logical PROPERTIES  PASS_REGULAR_EXPRESSION "1.*1" _BACKTRACE_TRIPLES "C:/Users/Vanek/source/repos/Algorithms3/Lab2CPP/CMakeLists.txt;22;add_test;C:/Users/Vanek/source/repos/Algorithms3/Lab2CPP/CMakeLists.txt;0;")
