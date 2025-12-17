project(Lab4CPP)

add_executable(Lab4CPP Lab4StrtuctV1.cpp)
target_link_libraries(Lab4CPP LibraryCPPTemplate)

add_test(NAME TestLab4CPP_Basic
    COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt A D)
    
add_test(NAME TestLab4CPP_Short
    COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt A B)
    
add_test(NAME TestLab4CPP_Same
    COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt A A)
    
set_tests_properties(
    TestLab4CPP_Basic
    TestLab4CPP_Short
    TestLab4CPP_Same
    PROPERTIES TIMEOUT 10)