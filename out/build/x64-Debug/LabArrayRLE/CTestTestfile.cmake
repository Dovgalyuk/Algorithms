# CMake generated Testfile for 
# Source directory: C:/Users/Asus/source/repos/Algorithms/LabArrayRLE
# Build directory: C:/Users/Asus/source/repos/Algorithms/out/build/x64-Debug/LabArrayRLE
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(RLE1 "C:/Users/Asus/source/repos/Algorithms/out/build/x64-Debug/LabArrayRLE/LabArrayRLE.exe" "C:/Users/Asus/source/repos/Algorithms/LabArrayRLE/input1.txt")
set_tests_properties(RLE1 PROPERTIES  PASS_REGULAR_EXPRESSION "1 4 2 2 3 3 5 1" _BACKTRACE_TRIPLES "C:/Users/Asus/source/repos/Algorithms/LabArrayRLE/CMakeLists.txt;11;add_test;C:/Users/Asus/source/repos/Algorithms/LabArrayRLE/CMakeLists.txt;0;")
add_test(RLE2 "C:/Users/Asus/source/repos/Algorithms/out/build/x64-Debug/LabArrayRLE/LabArrayRLE.exe" "C:/Users/Asus/source/repos/Algorithms/LabArrayRLE/input2.txt")
set_tests_properties(RLE2 PROPERTIES  PASS_REGULAR_EXPRESSION "1 1 2 1 3 1 4 1 5 1" _BACKTRACE_TRIPLES "C:/Users/Asus/source/repos/Algorithms/LabArrayRLE/CMakeLists.txt;22;add_test;C:/Users/Asus/source/repos/Algorithms/LabArrayRLE/CMakeLists.txt;0;")
add_test(RLE3 "C:/Users/Asus/source/repos/Algorithms/out/build/x64-Debug/LabArrayRLE/LabArrayRLE.exe" "C:/Users/Asus/source/repos/Algorithms/LabArrayRLE/input3.txt")
set_tests_properties(RLE3 PROPERTIES  PASS_REGULAR_EXPRESSION "7 8" _BACKTRACE_TRIPLES "C:/Users/Asus/source/repos/Algorithms/LabArrayRLE/CMakeLists.txt;33;add_test;C:/Users/Asus/source/repos/Algorithms/LabArrayRLE/CMakeLists.txt;0;")
add_test(RLE4 "C:/Users/Asus/source/repos/Algorithms/out/build/x64-Debug/LabArrayRLE/LabArrayRLE.exe" "C:/Users/Asus/source/repos/Algorithms/LabArrayRLE/input4.txt")
set_tests_properties(RLE4 PROPERTIES  PASS_REGULAR_EXPRESSION "0 2 -1 3 5 2 0 3" _BACKTRACE_TRIPLES "C:/Users/Asus/source/repos/Algorithms/LabArrayRLE/CMakeLists.txt;44;add_test;C:/Users/Asus/source/repos/Algorithms/LabArrayRLE/CMakeLists.txt;0;")
