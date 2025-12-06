add_executable(Lab3CPP main.cpp)
target_include_directories(Lab3CPP PRIVATE ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input1.txt ${CMAKE_CURRENT_BINARY_DIR}/input1.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input2.txt ${CMAKE_CURRENT_BINARY_DIR}/input2.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input3.txt ${CMAKE_CURRENT_BINARY_DIR}/input3.txt COPYONLY)

enable_testing()

############################
add_test(NAME TestLab3 COMMAND ${CMAKE_COMMAND} -E echo "Running TestLab3")
set_tests_properties(TestLab3 PROPERTIES FIXTURES_SETUP TestLab3Fixture)

add_test(NAME TestLab3_Run COMMAND $<TARGET_FILE:Lab3CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab3_Run PROPERTIES FIXTURES_REQUIRED TestLab3Fixture)
set_property(TEST TestLab3_Run PROPERTY ENVIRONMENT "TEST_OUTPUT=${CMAKE_CURRENT_BINARY_DIR}/testlab3_output.txt")
set_property(TEST TestLab3_Run PROPERTY PASS_REGULAR_EXPRESSION ".*")

add_test(NAME TestLab3_Verify COMMAND ${CMAKE_COMMAND} -E compare_files
    ${CMAKE_CURRENT_BINARY_DIR}/testlab3_output.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/expected_testlab3.txt
)
set_tests_properties(TestLab3_Verify PROPERTIES FIXTURES_CLEANUP TestLab3Fixture DEPENDS TestLab3_Run)

########################
add_test(NAME TestLab3_1 COMMAND ${CMAKE_COMMAND} -E echo "Running TestLab3_1")
set_tests_properties(TestLab3_1 PROPERTIES FIXTURES_SETUP TestLab3_1Fixture)

add_test(NAME TestLab3_1_Run COMMAND $<TARGET_FILE:Lab3CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(TestLab3_1_Run PROPERTIES FIXTURES_REQUIRED TestLab3_1Fixture)
set_property(TEST TestLab3_1_Run PROPERTY ENVIRONMENT "TEST_OUTPUT=${CMAKE_CURRENT_BINARY_DIR}/testlab3_1_output.txt")
set_property(TEST TestLab3_1_Run PROPERTY PASS_REGULAR_EXPRESSION ".*")

add_test(NAME TestLab3_1_Verify COMMAND ${CMAKE_COMMAND} -E compare_files
    ${CMAKE_CURRENT_BINARY_DIR}/testlab3_1_output.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/expected_testlab3_1.txt
)
set_tests_properties(TestLab3_1_Verify PROPERTIES FIXTURES_CLEANUP TestLab3_1Fixture DEPENDS TestLab3_1_Run)

##########################
add_test(NAME TestLab3_2 COMMAND ${CMAKE_COMMAND} -E echo "Running TestLab3_2")
set_tests_properties(TestLab3_2 PROPERTIES FIXTURES_SETUP TestLab3_2Fixture)

add_test(NAME TestLab3_2_Run COMMAND $<TARGET_FILE:Lab3CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(TestLab3_2_Run PROPERTIES FIXTURES_REQUIRED TestLab3_2Fixture)
set_property(TEST TestLab3_2_Run PROPERTY ENVIRONMENT "TEST_OUTPUT=${CMAKE_CURRENT_BINARY_DIR}/testlab3_2_output.txt")
set_property(TEST TestLab3_2_Run PROPERTY PASS_REGULAR_EXPRESSION ".*")

add_test(NAME TestLab3_2_Verify COMMAND ${CMAKE_COMMAND} -E compare_files
    ${CMAKE_CURRENT_BINARY_DIR}/testlab3_2_output.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/expected_testlab3_2.txt
)
set_tests_properties(TestLab3_2_Verify PROPERTIES FIXTURES_CLEANUP TestLab3_2Fixture DEPENDS TestLab3_2_Run)

###################
add_test(NAME TestLab3_3 COMMAND $<TARGET_FILE:Lab3CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab3_3 PROPERTY PASS_REGULAR_EXPRESSION "^-1\n$")