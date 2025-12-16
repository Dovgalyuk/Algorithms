add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab3CPP PUBLIC LibraryCPPTemplate)

add_test(NAME TestLab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt output.txt)

set_tests_properties(TestLab3CPP PROPERTIES
    PASS_REGULAR_EXPRESSION
    "3.*1 2 3.*4 5 6 7.*8 9"
)