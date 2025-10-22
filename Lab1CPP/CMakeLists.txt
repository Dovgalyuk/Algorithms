add_executable(Lab1CPP lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP PROPERTY PASS_REGULAR_EXPRESSION "change of sign: 0 unique values: 1 2 3 4 ")

add_test(NAME TestLab1CPP2 COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt)
set_property(TEST TestLab1CPP2 PROPERTY PASS_REGULAR_EXPRESSION "change of sign: 5 unique values: -1 2 3 4 6 ")