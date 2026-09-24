# CMake generated Testfile for 
# Source directory: C:/Users/Asus/source/repos/Algorithms/LabArrayStatistics
# Build directory: C:/Users/Asus/source/repos/Algorithms/out/build/x64-Debug/LabArrayStatistics
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Statistics1 "C:/Users/Asus/source/repos/Algorithms/out/build/x64-Debug/LabArrayStatistics/LabArrayStatistics.exe" "C:/Users/Asus/source/repos/Algorithms/LabArrayStatistics/input1.txt")
set_tests_properties(Statistics1 PROPERTIES  PASS_REGULAR_EXPRESSION "Positive: 4[
]+Negative: 3[
]+Zero: 3" _BACKTRACE_TRIPLES "C:/Users/Asus/source/repos/Algorithms/LabArrayStatistics/CMakeLists.txt;11;add_test;C:/Users/Asus/source/repos/Algorithms/LabArrayStatistics/CMakeLists.txt;0;")
add_test(Statistics2 "C:/Users/Asus/source/repos/Algorithms/out/build/x64-Debug/LabArrayStatistics/LabArrayStatistics.exe" "C:/Users/Asus/source/repos/Algorithms/LabArrayStatistics/input2.txt")
set_tests_properties(Statistics2 PROPERTIES  PASS_REGULAR_EXPRESSION "Positive: 5[
]+Negative: 0[
]+Zero: 0" _BACKTRACE_TRIPLES "C:/Users/Asus/source/repos/Algorithms/LabArrayStatistics/CMakeLists.txt;22;add_test;C:/Users/Asus/source/repos/Algorithms/LabArrayStatistics/CMakeLists.txt;0;")
add_test(Statistics3 "C:/Users/Asus/source/repos/Algorithms/out/build/x64-Debug/LabArrayStatistics/LabArrayStatistics.exe" "C:/Users/Asus/source/repos/Algorithms/LabArrayStatistics/input3.txt")
set_tests_properties(Statistics3 PROPERTIES  PASS_REGULAR_EXPRESSION "Positive: 0[
]+Negative: 5[
]+Zero: 0" _BACKTRACE_TRIPLES "C:/Users/Asus/source/repos/Algorithms/LabArrayStatistics/CMakeLists.txt;33;add_test;C:/Users/Asus/source/repos/Algorithms/LabArrayStatistics/CMakeLists.txt;0;")
add_test(Statistics4 "C:/Users/Asus/source/repos/Algorithms/out/build/x64-Debug/LabArrayStatistics/LabArrayStatistics.exe" "C:/Users/Asus/source/repos/Algorithms/LabArrayStatistics/input4.txt")
set_tests_properties(Statistics4 PROPERTIES  PASS_REGULAR_EXPRESSION "Positive: 0[
]+Negative: 0[
]+Zero: 5" _BACKTRACE_TRIPLES "C:/Users/Asus/source/repos/Algorithms/LabArrayStatistics/CMakeLists.txt;44;add_test;C:/Users/Asus/source/repos/Algorithms/LabArrayStatistics/CMakeLists.txt;0;")
