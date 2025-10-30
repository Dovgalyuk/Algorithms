add_executable(Lab1CPP lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1CPP_AllEqual COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab1CPP_AllEqual PROPERTY PASS_REGULAR_EXPRESSION
"150 1 4.*none")

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP PROPERTY PASS_REGULAR_EXPRESSION
"210 1 4.*195 190 200")

add_test(NAME TestLab1CPP_None COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab1CPP_None PROPERTY PASS_REGULAR_EXPRESSION
".*none")