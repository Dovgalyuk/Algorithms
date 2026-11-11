# CMake generated Testfile for 
# Source directory: /home/tbg/Karpenko-Maxim-5092/MazyLibrary
# Build directory: /home/tbg/Karpenko-Maxim-5092/MazyLibrary/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(vector_operations "/home/tbg/Karpenko-Maxim-5092/MazyLibrary/build/test_vector")
set_tests_properties(vector_operations PROPERTIES  _BACKTRACE_TRIPLES "/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;17;add_test;/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;0;")
add_test(queue_circular_buffer "/home/tbg/Karpenko-Maxim-5092/MazyLibrary/build/test_queue")
set_tests_properties(queue_circular_buffer PROPERTIES  _BACKTRACE_TRIPLES "/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;21;add_test;/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;0;")
add_test(maze_path "/usr/bin/cmake" "-DPROGRAM=/home/tbg/Karpenko-Maxim-5092/MazyLibrary/build/maze" "-DINPUT=/home/tbg/Karpenko-Maxim-5092/MazyLibrary/tests/maze_path.in" "-DEXPECTED=/home/tbg/Karpenko-Maxim-5092/MazyLibrary/tests/maze_path.out" "-P" "/home/tbg/Karpenko-Maxim-5092/MazyLibrary/tests/check.cmake")
set_tests_properties(maze_path PROPERTIES  _BACKTRACE_TRIPLES "/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;25;add_test;/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;34;add_maze_test;/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;0;")
add_test(maze_impossible "/usr/bin/cmake" "-DPROGRAM=/home/tbg/Karpenko-Maxim-5092/MazyLibrary/build/maze" "-DINPUT=/home/tbg/Karpenko-Maxim-5092/MazyLibrary/tests/maze_impossible.in" "-DEXPECTED=/home/tbg/Karpenko-Maxim-5092/MazyLibrary/tests/maze_impossible.out" "-P" "/home/tbg/Karpenko-Maxim-5092/MazyLibrary/tests/check.cmake")
set_tests_properties(maze_impossible PROPERTIES  _BACKTRACE_TRIPLES "/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;25;add_test;/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;35;add_maze_test;/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;0;")
add_test(maze_adjacent "/usr/bin/cmake" "-DPROGRAM=/home/tbg/Karpenko-Maxim-5092/MazyLibrary/build/maze" "-DINPUT=/home/tbg/Karpenko-Maxim-5092/MazyLibrary/tests/maze_adjacent.in" "-DEXPECTED=/home/tbg/Karpenko-Maxim-5092/MazyLibrary/tests/maze_adjacent.out" "-P" "/home/tbg/Karpenko-Maxim-5092/MazyLibrary/tests/check.cmake")
set_tests_properties(maze_adjacent PROPERTIES  _BACKTRACE_TRIPLES "/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;25;add_test;/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;36;add_maze_test;/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;0;")
add_test(maze_corridor "/usr/bin/cmake" "-DPROGRAM=/home/tbg/Karpenko-Maxim-5092/MazyLibrary/build/maze" "-DINPUT=/home/tbg/Karpenko-Maxim-5092/MazyLibrary/tests/maze_corridor.in" "-DEXPECTED=/home/tbg/Karpenko-Maxim-5092/MazyLibrary/tests/maze_corridor.out" "-P" "/home/tbg/Karpenko-Maxim-5092/MazyLibrary/tests/check.cmake")
set_tests_properties(maze_corridor PROPERTIES  _BACKTRACE_TRIPLES "/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;25;add_test;/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;37;add_maze_test;/home/tbg/Karpenko-Maxim-5092/MazyLibrary/CMakeLists.txt;0;")
