add_executable(Lab1CPP lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1CPP1 COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab1CPP1 PROPERTY PASS_REGULAR_EXPRESSION "1 1 2 6 24")

add_test(NAME TestLab1CPP2 COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab1CPP2 PROPERTY PASS_REGULAR_EXPRESSION "3 7")

add_test(NAME TestLab1CPP3 COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab1CPP3 PROPERTY PASS_REGULAR_EXPRESSION "")