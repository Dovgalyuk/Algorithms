add_executable(Lab4CPPTemplate lab4.cpp)
target_include_directories(Lab4CPPTemplate PUBLIC ../LibraryCPPTemplate)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt input.txt COPYONLY)

add_test(NAME KruskalTest COMMAND Lab4CPPTemplate input.txt)

set_tests_properties(KruskalTest PROPERTIES PASS_REGULAR_EXPRESSION "MST Weight: 19")