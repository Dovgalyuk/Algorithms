add_executable(AvlGenerator generator.cpp)
add_executable(AvlBenchmark benchmark.cpp)
target_include_directories(AvlBenchmark PUBLIC ../LibraryCPPTemplate)

set(DATA "${CMAKE_CURRENT_BINARY_DIR}/data")
file(MAKE_DIRECTORY "${DATA}")

add_test(NAME GEN_asc COMMAND AvlGenerator "${DATA}/mixed_asc.txt" 20000 1 asc 40000)
add_test(NAME GEN_desc COMMAND AvlGenerator "${DATA}/mixed_desc.txt" 20000 1 desc 40000)
add_test(NAME GEN_zigzag COMMAND AvlGenerator "${DATA}/mixed_zigzag.txt" 20000 1 zigzag 40000)
add_test(NAME GEN_random COMMAND AvlGenerator "${DATA}/mixed_random.txt" 20000 1 random 40000)
set_tests_properties(GEN_asc GEN_desc GEN_zigzag GEN_random PROPERTIES FIXTURES_SETUP gen)

add_test(NAME BENCHMARK COMMAND AvlBenchmark --sizes 1000,5000,10000 --repeat 3 --out "${CMAKE_CURRENT_BINARY_DIR}/benchmark.csv" "${DATA}/mixed_random.txt")
set_tests_properties(BENCHMARK PROPERTIES FIXTURES_REQUIRED gen)

add_test(NAME GEN_LARGE COMMAND AvlGenerator "${DATA}/large_random.txt" 1000000 1 random 1000000)
set_tests_properties(GEN_LARGE PROPERTIES FIXTURES_SETUP genlarge)

add_test(NAME BENCHMARK_LARGE_FILE COMMAND AvlBenchmark --sizes 1000,10000 --repeat 1 --out "${CMAKE_CURRENT_BINARY_DIR}/benchmark_large_file.csv" "${DATA}/large_random.txt")
set_tests_properties(BENCHMARK_LARGE_FILE PROPERTIES FIXTURES_REQUIRED genlarge)

set_tests_properties(GEN_asc GEN_desc GEN_zigzag GEN_random BENCHMARK GEN_LARGE BENCHMARK_LARGE_FILE PROPERTIES TIMEOUT 1)


add_test(NAME GEN_BENCH_asc COMMAND AvlGenerator "${DATA}/bench_asc.txt" 1000000 1 asc 0)
add_test(NAME GEN_BENCH_desc COMMAND AvlGenerator "${DATA}/bench_desc.txt" 1000000 1 desc 0)
add_test(NAME GEN_BENCH_zigzag COMMAND AvlGenerator "${DATA}/bench_zigzag.txt" 1000000 1 zigzag 0)
add_test(NAME GEN_BENCH_random COMMAND AvlGenerator "${DATA}/bench_random.txt" 1000000 1 random 0)
set_tests_properties(GEN_BENCH_asc GEN_BENCH_desc GEN_BENCH_zigzag GEN_BENCH_random PROPERTIES FIXTURES_SETUP genbench)

add_test(NAME BENCHMARK_FULL COMMAND AvlBenchmark --repeat 3 --out "${CMAKE_CURRENT_BINARY_DIR}/benchmark_full.csv" "${DATA}/bench_asc.txt" "${DATA}/bench_desc.txt" "${DATA}/bench_zigzag.txt" "${DATA}/bench_random.txt")
set_tests_properties(BENCHMARK_FULL PROPERTIES FIXTURES_REQUIRED genbench)

set_tests_properties(GEN_BENCH_asc GEN_BENCH_desc GEN_BENCH_zigzag GEN_BENCH_random BENCHMARK_FULL PROPERTIES LABELS full TIMEOUT 1800)