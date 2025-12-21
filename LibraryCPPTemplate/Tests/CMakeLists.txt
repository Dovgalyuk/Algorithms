project(LibraryCPPTemplateTests)

include_directories(..)

add_executable(TestVector vectorT.cpp)
add_executable(TestGraph graph.cpp)

enable_testing()
add_test(NAME TestVector COMMAND TestVector)
add_test(NAME TestGraph COMMAND TestGraph)
