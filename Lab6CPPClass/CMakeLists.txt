add_executable(Lab6CPPClass lab6.cpp)
target_include_directories(Lab6CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab6CPPClass LibraryCPPClass)

add_test(NAME Lab6_Benchmark_Run COMMAND Lab6CPPClass)