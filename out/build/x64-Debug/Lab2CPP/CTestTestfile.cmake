# CMake generated Testfile for 
# Source directory: C:/Users/Пользователь/source/repos/Algorithms/LAB2CPP
# Build directory: C:/Users/Пользователь/source/repos/Algorithms/out/build/x64-Debug/Lab2CPP
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Test_input "C:/Users/Пользователь/source/repos/Algorithms/out/build/x64-Debug/Lab2CPP/LAB2CPP.exe" "C:/Users/Пользователь/source/repos/Algorithms/LAB2CPP/input.txt")
set_tests_properties(Test_input PROPERTIES  PASS_REGULAR_EXPRESSION "YES" _BACKTRACE_TRIPLES "C:/Users/Пользователь/source/repos/Algorithms/LAB2CPP/CMakeLists.txt;5;add_test;C:/Users/Пользователь/source/repos/Algorithms/LAB2CPP/CMakeLists.txt;0;")
add_test(Test_1_yes "C:/Users/Пользователь/source/repos/Algorithms/out/build/x64-Debug/Lab2CPP/LAB2CPP.exe" "C:/Users/Пользователь/source/repos/Algorithms/LAB2CPP/test_input_1_YES.txt")
set_tests_properties(Test_1_yes PROPERTIES  PASS_REGULAR_EXPRESSION "YES" _BACKTRACE_TRIPLES "C:/Users/Пользователь/source/repos/Algorithms/LAB2CPP/CMakeLists.txt;8;add_test;C:/Users/Пользователь/source/repos/Algorithms/LAB2CPP/CMakeLists.txt;0;")
add_test(Test_2_NO "C:/Users/Пользователь/source/repos/Algorithms/out/build/x64-Debug/Lab2CPP/LAB2CPP.exe" "C:/Users/Пользователь/source/repos/Algorithms/LAB2CPP/test_input_3_NO.txt")
set_tests_properties(Test_2_NO PROPERTIES  PASS_REGULAR_EXPRESSION "NO" _BACKTRACE_TRIPLES "C:/Users/Пользователь/source/repos/Algorithms/LAB2CPP/CMakeLists.txt;11;add_test;C:/Users/Пользователь/source/repos/Algorithms/LAB2CPP/CMakeLists.txt;0;")
add_test(Test_4_NO "C:/Users/Пользователь/source/repos/Algorithms/out/build/x64-Debug/Lab2CPP/LAB2CPP.exe" "C:/Users/Пользователь/source/repos/Algorithms/LAB2CPP/test_input_4_NO.txt")
set_tests_properties(Test_4_NO PROPERTIES  PASS_REGULAR_EXPRESSION "NO" _BACKTRACE_TRIPLES "C:/Users/Пользователь/source/repos/Algorithms/LAB2CPP/CMakeLists.txt;14;add_test;C:/Users/Пользователь/source/repos/Algorithms/LAB2CPP/CMakeLists.txt;0;")
