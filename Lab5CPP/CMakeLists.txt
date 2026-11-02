add_executable(Lab5CPP main.cpp)
add_executable(Lab5Generator tests/generator.cpp)
add_executable(Lab5Benchmark tests/benchmark.cpp)

add_executable(Lab5Test tests/test_rb.cpp)
add_test(NAME TestLab5CPP COMMAND Lab5Test)