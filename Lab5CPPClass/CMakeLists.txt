add_executable(Lab5CPPClass lab5.cpp)
target_include_directories(Lab5CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab5CPPClass LibraryCPPClass)

add_test(NAME Lab5_Benchmark_Run COMMAND Lab5CPPClass)