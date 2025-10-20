add_executable(Lab2CPPClass calculon.cpp)
target_include_directories(Lab2CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPPClass LibraryCPPClass)

add_test(NAME TestCalculonBasic
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/test_combined.txt)

set_tests_properties(TestCalculonBasic PROPERTIES
    PASS_REGULAR_EXPRESSION "72 101 101 108 111 44 32 119 114 108 100 33"
)