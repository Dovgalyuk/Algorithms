add_executable(Lab6CPPTemplate main.cpp)
target_include_directories(Lab6CPPTemplate PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestLab6CPPTemplate COMMAND Lab6CPPTemplate)
set_tests_properties(TestLab6CPPTemplate PROPERTIES  PASS_REGULAR_EXPRESSION "All tests passed")