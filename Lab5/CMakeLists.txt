set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab5 main.cpp)

target_include_directories(Lab5 PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab5 LibraryCPPTemplate)

add_test(NAME BenchmarkOutputTest COMMAND Lab5)
set_tests_properties(BenchmarkOutputTest PROPERTIES
        PASS_REGULAR_EXPRESSION
        "Benchmark completed\\. Results saved to .+\\.csv\n\n=== Summary \\(N = [0-9]+\\) ===\nInsert:.*RH=[0-9]+\\.[0-9]+ ns/op, std=[0-9]+\\.[0-9]+ ns/op\nFind:.*RH=[0-9]+\\.[0-9]+ ns/op, std=[0-9]+\\.[0-9]+ ns/op\nErase:.*RH=[0-9]+\\.[0-9]+ ns/op, std=[0-9]+\\.[0-9]+ ns/op"
)
#add_subdirectory("Test")