# CMake generated Testfile for 
# Source directory: C:/Users/drozd/source/repos/Algorithms/Lab1C_PR
# Build directory: C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(TestLab1C_PR "C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/build/Debug/Lab1C_PR.exe" "C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/input.txt")
  set_tests_properties(TestLab1C_PR PROPERTIES  PASS_REGULAR_EXPRESSION "Task 4: Количество элементов > суммы \\(.*\\): 0;Task 5: Максимальная сумма 5 соседних: 114" _BACKTRACE_TRIPLES "C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/CMakeLists.txt;13;add_test;C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(TestLab1C_PR "C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/build/Release/Lab1C_PR.exe" "C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/input.txt")
  set_tests_properties(TestLab1C_PR PROPERTIES  PASS_REGULAR_EXPRESSION "Task 4: Количество элементов > суммы \\(.*\\): 0;Task 5: Максимальная сумма 5 соседних: 114" _BACKTRACE_TRIPLES "C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/CMakeLists.txt;13;add_test;C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(TestLab1C_PR "C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/build/MinSizeRel/Lab1C_PR.exe" "C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/input.txt")
  set_tests_properties(TestLab1C_PR PROPERTIES  PASS_REGULAR_EXPRESSION "Task 4: Количество элементов > суммы \\(.*\\): 0;Task 5: Максимальная сумма 5 соседних: 114" _BACKTRACE_TRIPLES "C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/CMakeLists.txt;13;add_test;C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(TestLab1C_PR "C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/build/RelWithDebInfo/Lab1C_PR.exe" "C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/input.txt")
  set_tests_properties(TestLab1C_PR PROPERTIES  PASS_REGULAR_EXPRESSION "Task 4: Количество элементов > суммы \\(.*\\): 0;Task 5: Максимальная сумма 5 соседних: 114" _BACKTRACE_TRIPLES "C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/CMakeLists.txt;13;add_test;C:/Users/drozd/source/repos/Algorithms/Lab1C_PR/CMakeLists.txt;0;")
else()
  add_test(TestLab1C_PR NOT_AVAILABLE)
endif()
subdirs("LibraryCPP")
