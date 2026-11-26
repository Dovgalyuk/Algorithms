add_test(NAME FordFulkerson_Basic
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(FordFulkerson_Basic PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 13")

add_test(NAME FordFulkerson_MultiPath
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(FordFulkerson_MultiPath PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 12")

add_test(NAME FordFulkerson_ParallelEdges
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_tests_properties(FordFulkerson_ParallelEdges PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 10")

add_test(NAME FordFulkerson_NoEdges
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_tests_properties(FordFulkerson_NoEdges PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 0")

add_test(NAME FordFulkerson_SingleEdge
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_tests_properties(FordFulkerson_SingleEdge PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 7")

add_test(NAME FordFulkerson_Chain
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input6.txt)
set_tests_properties(FordFulkerson_Chain PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 3")

add_test(NAME FordFulkerson_TwoParallelPaths
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input7.txt)
set_tests_properties(FordFulkerson_TwoParallelPaths PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 20")

add_test(NAME FordFulkerson_Bottleneck
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input8.txt)
set_tests_properties(FordFulkerson_Bottleneck PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 1")

add_test(NAME FordFulkerson_Disconnected
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input9.txt)
set_tests_properties(FordFulkerson_Disconnected PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 0")

add_test(NAME FordFulkerson_CityNames
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input10.txt)
set_tests_properties(FordFulkerson_CityNames PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 16")

add_test(NAME FordFulkerson_LargeCapacity
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input11.txt)
set_tests_properties(FordFulkerson_LargeCapacity PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 1000000")

add_test(NAME FordFulkerson_DiamondCross
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input12.txt)
set_tests_properties(FordFulkerson_DiamondCross PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 20")

add_test(NAME FordFulkerson_Cycle
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input13.txt)
set_tests_properties(FordFulkerson_Cycle PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 10")

add_test(NAME FordFulkerson_NoPathToSink
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input14.txt)
set_tests_properties(FordFulkerson_NoPathToSink PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 0")

add_test(NAME FordFulkerson_LongChain
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input15.txt)
set_tests_properties(FordFulkerson_LongChain PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 4")

add_test(NAME FordFulkerson_BackwardEdge
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input16.txt)
set_tests_properties(FordFulkerson_BackwardEdge PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 20")

add_test(NAME FordFulkerson_ZeroCapacity
    COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input17.txt)
set_tests_properties(FordFulkerson_ZeroCapacity PROPERTIES
    PASS_REGULAR_EXPRESSION "Max flow: 3")
