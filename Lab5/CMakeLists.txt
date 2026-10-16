add_executable(Lab5 lab5.cpp)
target_compile_features(Lab5 PRIVATE cxx_std_11)

add_executable(Lab5InterfaceTest interface_test.cpp)
target_compile_features(Lab5InterfaceTest PRIVATE cxx_std_11)

add_test(NAME TestLab5Interface COMMAND Lab5InterfaceTest)
add_test(NAME TestLab5Prefixes COMMAND Lab5 --test-prefixes)
add_test(NAME TestLab5Stress COMMAND Lab5 --test-stress 1000000)
add_test(NAME TestLab5Generator COMMAND Lab5 --test-generator ${CMAKE_CURRENT_BINARY_DIR}/generated.txt 1000)
add_test(NAME TestLab5Benchmark COMMAND Lab5 --test-benchmark ${CMAKE_CURRENT_BINARY_DIR}/benchmark-input.txt ${CMAKE_CURRENT_BINARY_DIR}/benchmark-test.csv)
set_tests_properties(TestLab5Stress PROPERTIES TIMEOUT 180)
set_tests_properties(TestLab5Benchmark PROPERTIES TIMEOUT 180)
