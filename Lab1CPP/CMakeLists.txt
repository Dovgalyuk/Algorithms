target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)

add_test(NAME TestLab1CPP COMMAND $<TARGET_FILE:Lab1CPP>)
set_tests_properties(TestLab1CPP PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    PASS_REGULAR_EXPRESSION "5,0 1 2 3 4 "
)
