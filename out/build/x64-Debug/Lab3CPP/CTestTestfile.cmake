# CMake generated Testfile for 
# Source directory: C:/Users/Vanek/source/repos/Algorithms3/Lab3CPP
# Build directory: C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab3CPP
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestLab3CPP "C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab3CPP/Lab3CPP.exe" "C:/Users/Vanek/source/repos/Algorithms3/Lab3CPP/test1_input.txt")
set_tests_properties(TestLab3CPP PROPERTIES  PASS_REGULAR_EXPRESSION "######
#xxxX#
#x####
#xxxY#
######" _BACKTRACE_TRIPLES "C:/Users/Vanek/source/repos/Algorithms3/Lab3CPP/CMakeLists.txt;5;add_test;C:/Users/Vanek/source/repos/Algorithms3/Lab3CPP/CMakeLists.txt;0;")
add_test(TestLab3CPP_2 "C:/Users/Vanek/source/repos/Algorithms3/out/build/x64-Debug/Lab3CPP/Lab3CPP.exe" "C:/Users/Vanek/source/repos/Algorithms3/Lab3CPP/test2_input.txt")
set_tests_properties(TestLab3CPP_2 PROPERTIES  PASS_REGULAR_EXPRESSION "IMPOSSIBLE" _BACKTRACE_TRIPLES "C:/Users/Vanek/source/repos/Algorithms3/Lab3CPP/CMakeLists.txt;13;add_test;C:/Users/Vanek/source/repos/Algorithms3/Lab3CPP/CMakeLists.txt;0;")
