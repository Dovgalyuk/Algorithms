add_executable(Lab1CPP main.cpp)
target_link_libraries(Lab1CPP LibraryCPPClass)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt 
               ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)

add_test(NAME Test_1 COMMAND Lab1CPP)
set_tests_properties(Test_1 PROPERTIES 
    PASS_REGULAR_EXPRESSION "0 1 2 3 4 5 6 7 8 9"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_test(NAME Test_2 COMMAND Lab1CPP)
set_tests_properties(Test_2 PROPERTIES 
    PASS_REGULAR_EXPRESSION "1 2 3 4"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)