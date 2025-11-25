add_executable(Lab4CPP lab4.cpp)
target_include_directories(Lab4CPP PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestLab4CPP COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab4CPP PROPERTY PASS_REGULAR_EXPRESSION "\\[2\\]  4   1   3   2   1.*\\[1\\] \\[2\\]  5   1   3   2.*3  \\[1\\] \\[2\\]  4   1   2.*2   3  \\[1\\] \\[2\\] \\[3\\] \\[1\\].*15")