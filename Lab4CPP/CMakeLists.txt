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

add_test(NAME TestLab4CPP_Check1 COMMAND Lab4CPP input.txt A D)
set_tests_properties(TestLab4CPP_Check1 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "Shortest distance: 3 edge\\(s\\)"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestLab4CPP_Check2 COMMAND Lab4CPP input1.txt A D)
set_tests_properties(TestLab4CPP_Check2 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "Shortest distance: 3 edge\\(s\\)"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestLab4CPP_Check3 COMMAND Lab4CPP input2.txt A D)
set_tests_properties(TestLab4CPP_Check3 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "Shortest distance: 2 edge\\(s\\)"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestLab4CPP_Check4 COMMAND Lab4CPP input3.txt A H)
set_tests_properties(TestLab4CPP_Check4 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "Shortest distance: 3 edge\\(s\\)"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestLab4CPP_Check5 COMMAND Lab4CPP input4.txt A C)
set_tests_properties(TestLab4CPP_Check5 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "No path found from A to C"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestLab4CPP_Check6 COMMAND Lab4CPP input5.txt A D)
set_tests_properties(TestLab4CPP_Check6 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "Shortest distance: 1 edge\\(s\\)"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestLab4CPP_FullCheck1 COMMAND Lab4CPP input.txt A D)
set_tests_properties(TestLab4CPP_FullCheck1 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "Shortest distance: 3 edge\\(s\\)[\r\n]+Number of shortest paths: 1"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestLab4CPP_FullCheck2 COMMAND Lab4CPP input1.txt A D)
set_tests_properties(TestLab4CPP_FullCheck2 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "Shortest distance: 3 edge\\(s\\)[\r\n]+Number of shortest paths: 1"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestLab4CPP_FullCheck3 COMMAND Lab4CPP input2.txt A D)
set_tests_properties(TestLab4CPP_FullCheck3 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "Shortest distance: 2 edge\\(s\\)[\r\n]+Number of shortest paths: 2"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestLab4CPP_FullCheck4 COMMAND Lab4CPP input3.txt A H)
set_tests_properties(TestLab4CPP_FullCheck4 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "Shortest distance: 3 edge\\(s\\)[\r\n]+Number of shortest paths: 5"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestLab4CPP_FullCheck6 COMMAND Lab4CPP input5.txt A D)
set_tests_properties(TestLab4CPP_FullCheck6 
    PROPERTIES 
    PASS_REGULAR_EXPRESSION "Shortest distance: 1 edge\\(s\\)[\r\n]+Number of shortest paths: 1"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

set_tests_properties(
    TestLab4CPP_Check1
    TestLab4CPP_Check2
    TestLab4CPP_Check3
    TestLab4CPP_Check4
    TestLab4CPP_Check5
    TestLab4CPP_Check6
    TestLab4CPP_FullCheck1
    TestLab4CPP_FullCheck2
    TestLab4CPP_FullCheck3
    TestLab4CPP_FullCheck4
    TestLab4CPP_FullCheck6
    PROPERTIES 
    TIMEOUT 10 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)