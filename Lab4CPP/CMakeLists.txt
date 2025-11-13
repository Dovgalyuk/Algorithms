add_executable(Lab4CPP lab4.cpp)
target_include_directories(Lab4CPP PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestLab4CPP COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab4CPP PROPERTIES PASS_REGULAR_EXPRESSION "16")

add_executable(GraphTest ../LibraryCPPTemplate/Tests/graph.cpp)
target_include_directories(GraphTest PUBLIC . ../LibraryCPPTemplate)

add_test(NAME GraphTest COMMAND GraphTest)
set_tests_properties(GraphTest PROPERTIES PASS_REGULAR_EXPRESSION "All graph tests passed!")