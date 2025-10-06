add_executable(Lab1CPP lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP PROPERTY PASS_REGULAR_EXPRESSION "More precipitation in the second half of June.\nThe most precipitation in the third decade of the month.\n2\n")

add_test(NAME TestLab1CPP2 COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab1CPP2 PROPERTY PASS_REGULAR_EXPRESSION "More precipitation in the first half of June.\nThe most precipitation in the first decade of the month.\n4\n")