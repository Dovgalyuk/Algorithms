add_executable(Lab4CPPTemplate main.cpp)
target_include_directories(Lab4CPPTemplate PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestLab4CPPTemplate
         COMMAND Lab4CPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab4CPPTemplate PROPERTIES
    PASS_REGULAR_EXPRESSION "Total cost: 7")
