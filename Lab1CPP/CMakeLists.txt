add_executable(Lab1CPP lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP PROPERTY PASS_REGULAR_EXPRESSION "Avg =4.5" "1 2 3 4 0" "разность:2")

add_test(NAME TestLab1CPP_2 COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab1CPP_2 PROPERTY PASS_REGULAR_EXPRESSION "Avg =0" "-5 -10" "разность:2")

add_test(NAME TestLab1CPP_3 COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab1CPP_3 PROPERTY PASS_REGULAR_EXPRESSION "Avg =4" "1 3" "четных нет")
