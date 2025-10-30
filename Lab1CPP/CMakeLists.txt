add_executable(Lab1CPP lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(TestLab1CPP PROPERTIES 
    PASS_REGULAR_EXPRESSION "7.*9 4 12 11 13"
)

add_test(NAME TestLab1CPP2 COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(TestLab1CPP2 PROPERTIES 
    PASS_REGULAR_EXPRESSION "0.*25 26 27 28 29"
)