add_executable(Lab5CPPGenerate generate.cpp)
add_executable(Lab5CPPStress stress.cpp)
add_executable(Lab5CPPBenchmark benchmark.cpp)

foreach(program Lab5CPPGenerate Lab5CPPStress Lab5CPPBenchmark)
    target_compile_features(${program} PRIVATE cxx_std_17)
    if(MSVC)
        target_compile_options(${program} PRIVATE /utf-8)
    endif()
endforeach()

target_include_directories(Lab5CPPStress PRIVATE ../LibraryCPP)
target_link_libraries(Lab5CPPStress PRIVATE LibraryCPP)
target_include_directories(Lab5CPPBenchmark PRIVATE ../LibraryCPP)
target_link_libraries(Lab5CPPBenchmark PRIVATE LibraryCPP)

function(add_avl_load_test name count order)
    set(input "${CMAKE_CURRENT_BINARY_DIR}/${name}.txt")
    add_test(NAME ${name}Generate COMMAND Lab5CPPGenerate "${input}" ${count} ${order})
    set_tests_properties(${name}Generate PROPERTIES FIXTURES_SETUP ${name} TIMEOUT 15)
    add_test(NAME ${name} COMMAND Lab5CPPStress "${input}" ${count})
    set_tests_properties(${name} PROPERTIES FIXTURES_REQUIRED ${name} TIMEOUT 30)
endfunction()

add_avl_load_test(TestLab5Million 1000000 ascending)
add_avl_load_test(TestLab5Descending 100000 descending)
add_avl_load_test(TestLab5Random 100000 random)

add_test(
    NAME TestLab5Benchmark
    COMMAND ${CMAKE_COMMAND}
        "-DPROGRAM=$<TARGET_FILE:Lab5CPPBenchmark>"
        "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/words.txt"
        "-DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/benchmark_test.csv"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/check_benchmark.cmake"
)
set_tests_properties(TestLab5Benchmark PROPERTIES TIMEOUT 15)

add_test(NAME TestLab5InvalidCount COMMAND Lab5CPPGenerate "${CMAKE_CURRENT_BINARY_DIR}/invalid.txt" -1 random)
add_test(NAME TestLab5InvalidOrder COMMAND Lab5CPPGenerate "${CMAKE_CURRENT_BINARY_DIR}/invalid.txt" 10 wrong)
add_test(NAME TestLab5MissingFile COMMAND Lab5CPPStress "${CMAKE_CURRENT_BINARY_DIR}/missing.txt" 10)
set_tests_properties(TestLab5InvalidCount TestLab5InvalidOrder TestLab5MissingFile
    PROPERTIES WILL_FAIL TRUE TIMEOUT 5)
