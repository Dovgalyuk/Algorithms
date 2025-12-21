project(Lab4CPP)

add_executable(Lab4CPP Lab4StrtuctV1.cpp)
target_link_libraries(Lab4CPP LibraryCPPTemplate)

add_test(NAME TestLab4CPP_Basic
    COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt A D)

add_test(NAME TestLab4CPP_Short
    COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt A B)

add_test(NAME TestLab4CPP_Same
    COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt A A)

add_test(NAME TestLab4CPP_MultiplePaths1
    COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt A D)

add_test(NAME TestLab4CPP_MultiplePaths2
    COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt A F)

add_test(NAME TestLab4CPP_NoPath
    COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt A C)

add_test(NAME TestLab4CPP_CompleteGraph
    COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt A E)


add_test(NAME TestLab4CPP COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt A D)
set_property(TEST TestLab4CPP PROPERTY PASS_REGULAR_EXPRESSION "Shortest distance: 3 edge(s)
Number of shortest paths: 1")

add_test(NAME TestLab4CPP2 COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt A D)
set_property(TEST TestLab4CPP2 PROPERTY PASS_REGULAR_EXPRESSION "Shortest distance: 3 edge(s)
Number of shortest paths: 1")

add_test(NAME TestLab4CPP3 COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt A D)
set_property(TEST TestLab4CPP3 PROPERTY PASS_REGULAR_EXPRESSION "Shortest distance: 2 edge(s)
Number of shortest paths: 2")

add_test(NAME TestLab4CPP4 COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt A H)
set_property(TEST TestLab4CPP4 PROPERTY PASS_REGULAR_EXPRESSION "Shortest distance: 3 edge(s)
Number of shortest paths: 5")

add_test(NAME TestLab4CPP5 COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt A C)
set_property(TEST TestLab4CPP5 PROPERTY PASS_REGULAR_EXPRESSION "No path found from A to C")

add_test(NAME TestLab4CPP6 COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt A D)
set_property(TEST TestLab4CPP6 PROPERTY PASS_REGULAR_EXPRESSION "Shortest distance: 1 edge(s)
Number of shortest paths: 1")

set_tests_properties(
    TestLab4CPP_Basic
    TestLab4CPP_Short
    TestLab4CPP_Same
    TestLab4CPP_MultiplePaths1
    TestLab4CPP_MultiplePaths2
    TestLab4CPP_NoPath
    TestLab4CPP_CompleteGraph
    TestLab4CPP
    TestLab4CPP2
    TestLab4CPP3
    TestLab4CPP4
    TestLab4CPP5
    TestLab4CPP6
    PROPERTIES TIMEOUT 10)