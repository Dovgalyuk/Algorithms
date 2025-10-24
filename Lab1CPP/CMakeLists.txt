add_executable(Lab1CPP lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab1CPP LibraryCPPTemplate)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set_tests_properties(TestLab1CPP PROPERTIES
    PASS_REGULAR_EXPRESSION
    "5.5.*15.5.*25.5.*1 4"
)
