add_executable(Lab4CPP lab4.cpp)
target_include_directories(Lab4CPP PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestLab4CPP COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab4CPP PROPERTY PASS_REGULAR_EXPRESSION "Path: .*(0, 0).*(1, 0).*(1, 1).*(2, 1).*(2, 2).*(3, 2).*(3, 3).*(3, 4).*(3, 5).*Cost: 15")