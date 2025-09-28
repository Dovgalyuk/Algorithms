# CMake generated Testfile for 
# Source directory: C:/Users/admin/Algorithms/StepanovLab1/Test
# Build directory: C:/Users/admin/Algorithms/StepanovLab1/Test/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(TestArrayCPPClass "C:/Users/admin/Algorithms/StepanovLab1/Test/build/Debug/lab1test.exe")
  set_tests_properties(TestArrayCPPClass PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/admin/Algorithms/StepanovLab1/Test/CMakeLists.txt;9;add_test;C:/Users/admin/Algorithms/StepanovLab1/Test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(TestArrayCPPClass "C:/Users/admin/Algorithms/StepanovLab1/Test/build/Release/lab1test.exe")
  set_tests_properties(TestArrayCPPClass PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/admin/Algorithms/StepanovLab1/Test/CMakeLists.txt;9;add_test;C:/Users/admin/Algorithms/StepanovLab1/Test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(TestArrayCPPClass "C:/Users/admin/Algorithms/StepanovLab1/Test/build/MinSizeRel/lab1test.exe")
  set_tests_properties(TestArrayCPPClass PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/admin/Algorithms/StepanovLab1/Test/CMakeLists.txt;9;add_test;C:/Users/admin/Algorithms/StepanovLab1/Test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(TestArrayCPPClass "C:/Users/admin/Algorithms/StepanovLab1/Test/build/RelWithDebInfo/lab1test.exe")
  set_tests_properties(TestArrayCPPClass PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/admin/Algorithms/StepanovLab1/Test/CMakeLists.txt;9;add_test;C:/Users/admin/Algorithms/StepanovLab1/Test/CMakeLists.txt;0;")
else()
  add_test(TestArrayCPPClass NOT_AVAILABLE)
endif()
