project(Lab4CPP)

add_executable(Lab4CPP Lab4StrtuctV1.cpp)

target_include_directories(Lab4CPP 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP
    ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPPTemplate
)

target_link_libraries(Lab4CPP LibraryCPPTemplate)
target_link_libraries(Lab4CPP LibraryCPP)

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

add_test(NAME Test1_MultiplePaths_output_test COMMAND Lab4StructV1 
    ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt A D)
set_tests_properties(Test1_MultiplePaths_output_test PROPERTIES
    PASS_REGULAR_EXPRESSION "(A-B-D.*A-C-D|A-C-D.*A-B-D)")

add_test(NAME Test2_FourPaths_output_test COMMAND Lab4StructV1 
    ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt A G)
set_tests_properties(Test2_FourPaths_output_test PROPERTIES
    PASS_REGULAR_EXPRESSION ".*A-B-G.*A-C-G.*A-D-G")

add_test(NAME Test3_CompleteGraph_output_test COMMAND Lab4StructV1 
    ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt A B)
set_tests_properties(Test3_CompleteGraph_output_test PROPERTIES
    PASS_REGULAR_EXPRESSION "A-B")

add_test(NAME Test4_NoPath_output_test COMMAND Lab4StructV1 
    ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt A Z)
set_tests_properties(Test4_NoPath_output_test PROPERTIES
    PASS_REGULAR_EXPRESSION "Error: Target vertex 'Z' not found")

add_test(NAME Test5_SameVertex_output_test COMMAND Lab4StructV1 
    ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt A A)
set_tests_properties(Test5_SameVertex_output_test PROPERTIES
    PASS_REGULAR_EXPRESSION "A")
    
add_test(NAME Test6_inputTXT_output_test COMMAND Lab4StructV1 
    ${CMAKE_CURRENT_SOURCE_DIR}/input.txt A B)
set_tests_properties(Test6_inputTXT_output_test PROPERTIES
    PASS_REGULAR_EXPRESSION "A")

set_tests_properties(
    TestLab4CPP_Basic
    TestLab4CPP_Short
    TestLab4CPP_Same
    TestLab4CPP_MultiplePaths1
    TestLab4CPP_MultiplePaths2
    TestLab4CPP_NoPath
    TestLab4CPP_CompleteGraph
    Test1_MultiplePaths_output_test
    Test2_FourPaths_output_test
    Test3_CompleteGraph_output_test
    Test4_NoPath_output_test
    Test5_SameVertex_output_test
    Test6_inputTXT_output_test
    PROPERTIES TIMEOUT 10)
