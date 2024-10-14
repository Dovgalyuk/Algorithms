# CMake generated Testfile for 
# Source directory: D:/НовГУ. Довгалюк/Algorithms/Lab1CPP
# Build directory: D:/НовГУ. Довгалюк/Algorithms/build/Lab1CPP
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(TestLab1CPP "D:/НовГУ. Довгалюк/Algorithms/build/Lab1CPP/Debug/Lab1CPP.exe" "D:/НовГУ. Довгалюк/Algorithms/Lab1CPP/input.txt")
  set_tests_properties(TestLab1CPP PROPERTIES  _BACKTRACE_TRIPLES "D:/НовГУ. Довгалюк/Algorithms/Lab1CPP/CMakeLists.txt;5;add_test;D:/НовГУ. Довгалюк/Algorithms/Lab1CPP/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(TestLab1CPP "D:/НовГУ. Довгалюк/Algorithms/build/Lab1CPP/Release/Lab1CPP.exe" "D:/НовГУ. Довгалюк/Algorithms/Lab1CPP/input.txt")
  set_tests_properties(TestLab1CPP PROPERTIES  _BACKTRACE_TRIPLES "D:/НовГУ. Довгалюк/Algorithms/Lab1CPP/CMakeLists.txt;5;add_test;D:/НовГУ. Довгалюк/Algorithms/Lab1CPP/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(TestLab1CPP "D:/НовГУ. Довгалюк/Algorithms/build/Lab1CPP/MinSizeRel/Lab1CPP.exe" "D:/НовГУ. Довгалюк/Algorithms/Lab1CPP/input.txt")
  set_tests_properties(TestLab1CPP PROPERTIES  _BACKTRACE_TRIPLES "D:/НовГУ. Довгалюк/Algorithms/Lab1CPP/CMakeLists.txt;5;add_test;D:/НовГУ. Довгалюк/Algorithms/Lab1CPP/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(TestLab1CPP "D:/НовГУ. Довгалюк/Algorithms/build/Lab1CPP/RelWithDebInfo/Lab1CPP.exe" "D:/НовГУ. Довгалюк/Algorithms/Lab1CPP/input.txt")
  set_tests_properties(TestLab1CPP PROPERTIES  _BACKTRACE_TRIPLES "D:/НовГУ. Довгалюк/Algorithms/Lab1CPP/CMakeLists.txt;5;add_test;D:/НовГУ. Довгалюк/Algorithms/Lab1CPP/CMakeLists.txt;0;")
else()
  add_test(TestLab1CPP NOT_AVAILABLE)
endif()
