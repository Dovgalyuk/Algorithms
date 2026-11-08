add_executable(Lab3 lab3.cpp)
target_include_directories(Lab3 PUBLIC ../LibraryCPP)
target_link_libraries(Lab3 LibraryCPP)

add_test(NAME TestLab3 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab3 PROPERTY PASS_REGULAR_EXPRESSION "#########[\r\n]+#\\.\\.#\\.\\.\\.0#[\r\n]+#\\.\\.\\.\\.\\.\\.\\.#[\r\n]+#\\.\\.\\.#1###[\r\n]+#\\.\\.\\.#2\\.3#[\r\n]+#########")

add_test(NAME TestLab3_Direct COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab3_Direct PROPERTY PASS_REGULAR_EXPRESSION "#####[\r\n]+#0\\.1#[\r\n]+#####")

add_test(NAME TestLab3_Diagonal COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab3_Diagonal PROPERTY PASS_REGULAR_EXPRESSION "######[\r\n]+#0\\.\\.\\.#[\r\n]+#\\.\\.\\.\\.#[\r\n]+#\\.\\.\\.\\.#[\r\n]+#\\.\\.\\.1#[\r\n]+######")

add_test(NAME TestLab3_NoPath COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab3_NoPath PROPERTY PASS_REGULAR_EXPRESSION "No path")

add_test(NAME TestLab3_Spiral COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST TestLab3_Spiral PROPERTY PASS_REGULAR_EXPRESSION "#########[\r\n]+#0\\.\\.\\.\\.\\.1#[\r\n]+#######\\.#[\r\n]+#3\\.\\.\\.\\.\\.2#[\r\n]+#\\.#######[\r\n]+#4\\.\\.\\.\\.\\.5#[\r\n]+#######\\.#[\r\n]+#7\\.\\.\\.\\.\\.6#[\r\n]+#########")

add_test(NAME TestLab3_Corridor COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input6.txt)
set_property(TEST TestLab3_Corridor PROPERTY PASS_REGULAR_EXPRESSION "##########[\r\n]+#0\\.\\.\\.\\.\\.1##[\r\n]+#######\\.##[\r\n]+#\\.3\\.\\.\\.\\.2##[\r\n]+##\\.#######[\r\n]+##4\\.\\.\\.\\.\\.5#[\r\n]+##########")

add_test(NAME TestLab3_Obstacles COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input7.txt)
set_property(TEST TestLab3_Obstacles PROPERTY PASS_REGULAR_EXPRESSION "#########[\r\n]+#0#\\.3\\.\\.4#[\r\n]+#1#\\.###\\.#[\r\n]+#\\.2\\.#\\.\\.\\.#[\r\n]+###\\.#\\.#\\.#[\r\n]+#\\.\\.\\.#\\.\\.5#[\r\n]+#########")

add_test(NAME TestLab3_Letters COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input8.txt)
set_property(TEST TestLab3_Letters PROPERTY PASS_REGULAR_EXPRESSION "############[\r\n]+#0\\.\\.\\.\\.\\.\\.\\.\\.1#[\r\n]+##########\\.#[\r\n]+#3\\.\\.\\.\\.\\.\\.\\.\\.2#[\r\n]+#\\.##########[\r\n]+#4\\.\\.\\.\\.\\.\\.\\.\\.5#[\r\n]+##########\\.#[\r\n]+#7\\.\\.\\.\\.\\.\\.\\.\\.6#[\r\n]+#\\.##########[\r\n]+#8\\.\\.\\.\\.\\.\\.\\.\\.9#[\r\n]+##########\\.#[\r\n]+#B\\.\\.\\.\\.\\.\\.\\.\\.A#[\r\n]+#\\.##########[\r\n]+#C\\.\\.\\.\\.\\.\\.\\.\\.D#[\r\n]+############")