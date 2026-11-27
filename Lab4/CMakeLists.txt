add_executable(Lab4 lab4.cpp)
target_include_directories(Lab4 PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestLab4_1 COMMAND Lab4 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab4_1 PROPERTY PASS_REGULAR_EXPRESSION "C D 4[\r\n]+A D 5[\r\n]+A B 10[\r\n]+Total: 19")

add_test(NAME TestLab4_2 COMMAND Lab4 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab4_2 PROPERTY PASS_REGULAR_EXPRESSION "5 6 12[\r\n]+3 4 16[\r\n]+1 2 18[\r\n]+2 3 19[\r\n]+4 5 22[\r\n]+Total: 87")

add_test(NAME TestLab4_3 COMMAND Lab4 ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab4_3 PROPERTY PASS_REGULAR_EXPRESSION "D E -2[\r\n]+B C 0[\r\n]+A B 2[\r\n]+B D 4[\r\n]+Total: 4")

add_test(NAME TestLab4_4 COMMAND Lab4 ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab4_4 PROPERTY PASS_REGULAR_EXPRESSION "No spanning tree")

add_test(NAME TestLab4_5 COMMAND Lab4 ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST TestLab4_5 PROPERTY PASS_REGULAR_EXPRESSION "Total: 0")

add_test(NAME TestLab4_6 COMMAND Lab4 ${CMAKE_CURRENT_SOURCE_DIR}/input6.txt)
set_property(TEST TestLab4_6 PROPERTY PASS_REGULAR_EXPRESSION "No spanning tree")

add_test(NAME TestLab4_7 COMMAND Lab4 ${CMAKE_CURRENT_SOURCE_DIR}/input7.txt)
set_property(TEST TestLab4_7 PROPERTY PASS_REGULAR_EXPRESSION "Y X 4[\r\n]+Y Z 6[\r\n]+Total: 10")

add_test(NAME TestLab4_8 COMMAND Lab4 ${CMAKE_CURRENT_SOURCE_DIR}/input8.txt)
set_property(TEST TestLab4_8 PROPERTY PASS_REGULAR_EXPRESSION "10 20 5[\r\n]+10 30 5[\r\n]+10 50 5[\r\n]+20 40 5[\r\n]+Total: 20")

add_test(NAME TestLab4_9 COMMAND Lab4 ${CMAKE_CURRENT_SOURCE_DIR}/input9.txt)
set_property(TEST TestLab4_9 PROPERTY PASS_REGULAR_EXPRESSION "1 2 1000000000[\r\n]+2 3 1000000000[\r\n]+3 4 1000000000[\r\n]+Total: 3000000000")

add_test(NAME TestLab4_10 COMMAND Lab4 ${CMAKE_CURRENT_SOURCE_DIR}/input10.txt)
set_property(TEST TestLab4_10 PROPERTY PASS_REGULAR_EXPRESSION "node-a Node-a 2[\r\n]+node-a mid_point_999 3[\r\n]+mid_point_999 very_long_destination_vertex_name 5[\r\n]+vertex_start_001 node-a 7[\r\n]+Total: 17")