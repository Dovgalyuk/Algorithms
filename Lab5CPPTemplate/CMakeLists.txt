add_executable(Lab5CPPTemplate main.cpp)
target_include_directories(Lab5CPPTemplate PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestLab5CPPTemplate COMMAND Lab5CPPTemplate)
set_tests_properties(TestLab5CPPTemplate PROPERTIES
    PASS_REGULAR_EXPRESSION "Items \\(N\\)(.|\\n)+10000")
