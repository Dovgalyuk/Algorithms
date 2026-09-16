# CMake generated Testfile for 
# Source directory: C:/Users/cloud/Algorithms
# Build directory: C:/Users/cloud/Algorithms/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(grades_test "C:/Users/cloud/Algorithms/build/task1.exe" "C:/Users/cloud/Algorithms/tests/grades_input.txt" "C:/Users/cloud/Algorithms/build/grades_output.txt")
set_tests_properties(grades_test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/cloud/Algorithms/CMakeLists.txt;12;add_test;C:/Users/cloud/Algorithms/CMakeLists.txt;0;")
add_test(grades_check "C:/Users/cloud/AppData/Local/Microsoft/WinGet/Packages/BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe/mingw64/bin/cmake.exe" "-E" "compare_files" "C:/Users/cloud/Algorithms/build/grades_output.txt" "C:/Users/cloud/Algorithms/tests/grades_expected.txt")
set_tests_properties(grades_check PROPERTIES  DEPENDS "grades_test" _BACKTRACE_TRIPLES "C:/Users/cloud/Algorithms/CMakeLists.txt;18;add_test;C:/Users/cloud/Algorithms/CMakeLists.txt;0;")
add_test(grades_test_2 "C:/Users/cloud/Algorithms/build/task1.exe" "C:/Users/cloud/Algorithms/tests/grades_input_2.txt" "C:/Users/cloud/Algorithms/build/grades_output_2.txt")
set_tests_properties(grades_test_2 PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/cloud/Algorithms/CMakeLists.txt;26;add_test;C:/Users/cloud/Algorithms/CMakeLists.txt;0;")
add_test(grades_check_2 "C:/Users/cloud/AppData/Local/Microsoft/WinGet/Packages/BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe/mingw64/bin/cmake.exe" "-E" "compare_files" "C:/Users/cloud/Algorithms/build/grades_output_2.txt" "C:/Users/cloud/Algorithms/tests/grades_expected_2.txt")
set_tests_properties(grades_check_2 PROPERTIES  DEPENDS "grades_test_2" _BACKTRACE_TRIPLES "C:/Users/cloud/Algorithms/CMakeLists.txt;32;add_test;C:/Users/cloud/Algorithms/CMakeLists.txt;0;")
add_test(rle_test "C:/Users/cloud/Algorithms/build/task2.exe" "C:/Users/cloud/Algorithms/tests/rle_input.txt" "C:/Users/cloud/Algorithms/build/rle_output.txt")
set_tests_properties(rle_test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/cloud/Algorithms/CMakeLists.txt;40;add_test;C:/Users/cloud/Algorithms/CMakeLists.txt;0;")
add_test(rle_check "C:/Users/cloud/AppData/Local/Microsoft/WinGet/Packages/BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe/mingw64/bin/cmake.exe" "-E" "compare_files" "C:/Users/cloud/Algorithms/build/rle_output.txt" "C:/Users/cloud/Algorithms/tests/rle_expected.txt")
set_tests_properties(rle_check PROPERTIES  DEPENDS "rle_test" _BACKTRACE_TRIPLES "C:/Users/cloud/Algorithms/CMakeLists.txt;46;add_test;C:/Users/cloud/Algorithms/CMakeLists.txt;0;")
add_test(rle_test_2 "C:/Users/cloud/Algorithms/build/task2.exe" "C:/Users/cloud/Algorithms/tests/rle_input_2.txt" "C:/Users/cloud/Algorithms/build/rle_output_2.txt")
set_tests_properties(rle_test_2 PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/cloud/Algorithms/CMakeLists.txt;54;add_test;C:/Users/cloud/Algorithms/CMakeLists.txt;0;")
add_test(rle_check_2 "C:/Users/cloud/AppData/Local/Microsoft/WinGet/Packages/BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe/mingw64/bin/cmake.exe" "-E" "compare_files" "C:/Users/cloud/Algorithms/build/rle_output_2.txt" "C:/Users/cloud/Algorithms/tests/rle_expected_2.txt")
set_tests_properties(rle_check_2 PROPERTIES  DEPENDS "rle_test_2" _BACKTRACE_TRIPLES "C:/Users/cloud/Algorithms/CMakeLists.txt;60;add_test;C:/Users/cloud/Algorithms/CMakeLists.txt;0;")
