add_executable(ShortestPath shortest_path.cpp)

target_include_directories(ShortestPath PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestShortestPathByInput1 COMMAND ShortestPath ${CMAKE_CURRENT_SOURCE_DIR}/ShortestPathTestData/input1.txt output1.txt)
set_property(TEST TestShortestPathByInput1 PROPERTY PASS_REGULAR_EXPRESSION "Start City1 City2 End")

add_test(NAME TestShortestPathByInput2 COMMAND ShortestPath ${CMAKE_CURRENT_SOURCE_DIR}/ShortestPathTestData/input2.txt output2.txt)
set_property(TEST TestShortestPathByInput2 PROPERTY PASS_REGULAR_EXPRESSION "Los_Santos Liberty_City Vice_City")

add_test(NAME TestShortestPathByInput3 COMMAND ShortestPath ${CMAKE_CURRENT_SOURCE_DIR}/ShortestPathTestData/input3.txt output3.txt)
set_property(TEST TestShortestPathByInput3 PROPERTY PASS_REGULAR_EXPRESSION "A B C")

add_test(NAME TestShortestPathByInput4 COMMAND ShortestPath ${CMAKE_CURRENT_SOURCE_DIR}/ShortestPathTestData/input4.txt output4.txt)
set_property(TEST TestShortestPathByInput4 PROPERTY PASS_REGULAR_EXPRESSION "^[Bb][\r\n]*$")

add_test(NAME TestShortestPathByInput5 COMMAND ShortestPath ${CMAKE_CURRENT_SOURCE_DIR}/ShortestPathTestData/input5.txt output5.txt)
set_property(TEST TestShortestPathByInput5 PROPERTY PASS_REGULAR_EXPRESSION "No path")