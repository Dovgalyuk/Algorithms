project(Lab4CPP)

add_executable(Lab4CPP Lab4StrtuctV1.cpp)
target_link_libraries(Lab4CPP LibraryCPPTemplate)

set(INPUT_FILES
    input.txt
    input1.txt
    input2.txt
    input3.txt
    input4.txt
    input5.txt
)

foreach(input_file IN LISTS INPUT_FILES)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/${input_file}
        ${CMAKE_CURRENT_BINARY_DIR}/${input_file}
        COPYONLY
    )
endforeach()

add_test(NAME TestLab4CPP_Basic
    COMMAND Lab4CPP input1.txt A D)

add_test(NAME TestLab4CPP_Short
    COMMAND Lab4CPP input1.txt A B)

add_test(NAME TestLab4CPP_Same
    COMMAND Lab4CPP input1.txt A A)

add_test(NAME TestLab4CPP_MultiplePaths1
    COMMAND Lab4CPP input2.txt A D)

add_test(NAME TestLab4CPP_MultiplePaths2
    COMMAND Lab4CPP input3.txt A F)

add_test(NAME TestLab4CPP_NoPath
    COMMAND Lab4CPP input4.txt A C)

add_test(NAME TestLab4CPP_CompleteGraph
    COMMAND Lab4CPP input5.txt A E)

add_test(NAME TestLab4CPP_Check1 COMMAND Lab4CPP input.txt A D)
set_tests_properties(TestLab4CPP_Check1 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "Shortest distance: 3 edge.s."
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestLab4CPP_Check2 COMMAND Lab4CPP input1.txt A D)
set_tests_properties(TestLab4CPP_Check2 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "Shortest distance: 3 edge.s."
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestLab4CPP_Check3 COMMAND Lab4CPP input2.txt A D)
set_tests_properties(TestLab4CPP_Check3 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "Shortest distance: 2 edge.s."
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestLab4CPP_Check4 COMMAND Lab4CPP input3.txt A H)
set_tests_properties(TestLab4CPP_Check4 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "Shortest distance: 3 edge.s."
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestLab4CPP_Check5 COMMAND Lab4CPP input4.txt A C)
set_tests_properties(TestLab4CPP_Check5 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "No path found from A to C"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestLab4CPP_Check6 COMMAND Lab4CPP input5.txt A D)
set_tests_properties(TestLab4CPP_Check6 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "Shortest distance: 1 edge.s."
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

set_tests_properties(
    TestLab4CPP_Basic
    TestLab4CPP_Short
    TestLab4CPP_Same
    TestLab4CPP_MultiplePaths1
    TestLab4CPP_MultiplePaths2
    TestLab4CPP_NoPath
    TestLab4CPP_CompleteGraph
    TestLab4CPP_Check1
    TestLab4CPP_Check2
    TestLab4CPP_Check3
    TestLab4CPP_Check4
    TestLab4CPP_Check5
    TestLab4CPP_Check6
    PROPERTIES 
    TIMEOUT 10 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)