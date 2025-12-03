add_executable(Lab5Cpp lab5.cpp)
target_include_directories(Lab5Cpp PUBLIC ../LibraryCPP)
target_link_libraries(Lab5Cpp LibraryCPP)

add_test(NAME Lab5Benchmark COMMAND Lab5Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST Lab5Benchmark PROPERTY TIMEOUT 1000)