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

set_tests_properties(
    TestLab4CPP_Basic
    TestLab4CPP_Short
    TestLab4CPP_Same
    TestLab4CPP_MultiplePaths1
    TestLab4CPP_MultiplePaths2
    TestLab4CPP_NoPath
    TestLab4CPP_CompleteGraph
    PROPERTIES TIMEOUT 10)
