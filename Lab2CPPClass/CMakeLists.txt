add_executable(Lab2CPPClass calculon.cpp)
target_include_directories(Lab2CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPPClass LibraryCPPClass)

add_test(NAME TestCalculonBasic
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/test_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/test_input.txt)

set_tests_properties(TestCalculonBasic PROPERTIES
    PASS_REGULAR_EXPRESSION "72 101 101 108 111 44 32 119 114 108 100 33"
)

add_test(NAME TestCalculonSimple
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/test_script2.txt ${CMAKE_CURRENT_SOURCE_DIR}/test_input2.txt)

set_tests_properties(TestCalculonSimple PROPERTIES
    PASS_REGULAR_EXPRESSION "15 10 10"
)

add_test(NAME TestCalculonSequence
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/test_script3.txt ${CMAKE_CURRENT_SOURCE_DIR}/test_input3.txt)

set_tests_properties(TestCalculonSequence PROPERTIES
    PASS_REGULAR_EXPRESSION "4 3 2 1"
)