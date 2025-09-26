# CMake generated Testfile for 
# Source directory: C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass
# Build directory: C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(TestLab1CPPClass "C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/build/Debug/lab1cppclass.exe" "C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/input.txt")
  set_tests_properties(TestLab1CPPClass PROPERTIES  PASS_REGULAR_EXPRESSION "12 4" _BACKTRACE_TRIPLES "C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/CMakeLists.txt;11;add_test;C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(TestLab1CPPClass "C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/build/Release/lab1cppclass.exe" "C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/input.txt")
  set_tests_properties(TestLab1CPPClass PROPERTIES  PASS_REGULAR_EXPRESSION "12 4" _BACKTRACE_TRIPLES "C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/CMakeLists.txt;11;add_test;C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(TestLab1CPPClass "C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/build/MinSizeRel/lab1cppclass.exe" "C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/input.txt")
  set_tests_properties(TestLab1CPPClass PROPERTIES  PASS_REGULAR_EXPRESSION "12 4" _BACKTRACE_TRIPLES "C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/CMakeLists.txt;11;add_test;C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(TestLab1CPPClass "C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/build/RelWithDebInfo/lab1cppclass.exe" "C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/input.txt")
  set_tests_properties(TestLab1CPPClass PROPERTIES  PASS_REGULAR_EXPRESSION "12 4" _BACKTRACE_TRIPLES "C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/CMakeLists.txt;11;add_test;C:/Users/admin/Algorithms/StepanovLab1/Lab1CPPClass/CMakeLists.txt;0;")
else()
  add_test(TestLab1CPPClass NOT_AVAILABLE)
endif()
