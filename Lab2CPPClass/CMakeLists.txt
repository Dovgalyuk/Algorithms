add_executable(Lab2 lab2.cpp)
target_include_directories(Lab2 PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2 LibraryCPPClass)

add_test(NAME TestLab2_Work COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab2_Work PROPERTY PASS_REGULAR_EXPRESSION "YES")

add_test(NAME TestLab2_Wrong COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab2_Wrong PROPERTY PASS_REGULAR_EXPRESSION "NO")

add_test(NAME TestLab2_Different COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab2_Different PROPERTY PASS_REGULAR_EXPRESSION "YES")

add_test(NAME TestLab2_Order COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab2_Order PROPERTY PASS_REGULAR_EXPRESSION "NO")

add_test(NAME TestLab2_Unclosed COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST TestLab2_Unclosed PROPERTY PASS_REGULAR_EXPRESSION "NO")
