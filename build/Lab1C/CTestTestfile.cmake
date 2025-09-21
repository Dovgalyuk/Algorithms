# CMake generated Testfile for 
# Source directory: C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/Lab1C
# Build directory: C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/build/Lab1C
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(TestLab1C "C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/build/Lab1C/Debug/Lab1C.exe" "C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/Lab1C/input.txt")
  set_tests_properties(TestLab1C PROPERTIES  PASS_REGULAR_EXPRESSION "1 2 3 4 5" _BACKTRACE_TRIPLES "C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/Lab1C/CMakeLists.txt;5;add_test;C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/Lab1C/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(TestLab1C "C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/build/Lab1C/Release/Lab1C.exe" "C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/Lab1C/input.txt")
  set_tests_properties(TestLab1C PROPERTIES  PASS_REGULAR_EXPRESSION "1 2 3 4 5" _BACKTRACE_TRIPLES "C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/Lab1C/CMakeLists.txt;5;add_test;C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/Lab1C/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(TestLab1C "C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/build/Lab1C/MinSizeRel/Lab1C.exe" "C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/Lab1C/input.txt")
  set_tests_properties(TestLab1C PROPERTIES  PASS_REGULAR_EXPRESSION "1 2 3 4 5" _BACKTRACE_TRIPLES "C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/Lab1C/CMakeLists.txt;5;add_test;C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/Lab1C/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(TestLab1C "C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/build/Lab1C/RelWithDebInfo/Lab1C.exe" "C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/Lab1C/input.txt")
  set_tests_properties(TestLab1C PROPERTIES  PASS_REGULAR_EXPRESSION "1 2 3 4 5" _BACKTRACE_TRIPLES "C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/Lab1C/CMakeLists.txt;5;add_test;C:/Users/УченикТОР/Desktop/Новая папка (3)/Algorithms/Lab1C/CMakeLists.txt;0;")
else()
  add_test(TestLab1C NOT_AVAILABLE)
endif()
