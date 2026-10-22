add_executable(lab3 lab3.cpp)
target_include_directories(lab3 PUBLIC ../LibraryCPP)
target_link_libraries(lab3 LibraryCPP)

add_test(NAME TestLab3_Example COMMAND lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab3_Example PROPERTY PASS_REGULAR_EXPRESSION "#\\.\\.\\.#2\\.3#")

add_test(NAME TestLab3_Diag COMMAND lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab3_Diag PROPERTY PASS_REGULAR_EXPRESSION "#\\.1\\.#")

add_test(NAME TestLab3_Vert COMMAND lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab3_Vert PROPERTY PASS_REGULAR_EXPRESSION "#3#\\.\\.\\.\\.\\.9#")

add_test(NAME TestLab3_NoPath COMMAND lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab3_NoPath PROPERTY FAIL_REGULAR_EXPRESSION "[0-9]")
