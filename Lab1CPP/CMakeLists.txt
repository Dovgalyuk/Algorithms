add_executable(Lab1CPP "lab1.cpp")
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP PROPERTY PASS_REGULAR_EXPRESSION "Task 1: Max = 9, first index = 1, last index = 9.*Task 2: Most frequent = 3 \\(occurs 3 times\\)")
