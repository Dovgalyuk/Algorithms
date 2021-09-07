add_executable(First test.cpp)

add_executable(TestContainer ../../LibraryCPP/Tests/array.cpp)
target_include_directories(TestContainer PUBLIC ../../Algorithms/First)
add_test(TestContainer TestContainer)