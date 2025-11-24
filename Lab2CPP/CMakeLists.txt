add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab2CPP PUBLIC LibraryCPPTemplate)

add_test(NAME TestLab2CPP COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt output.txt)

set_tests_properties(TestLab2CPP PROPERTIES
    PASS_REGULAR_EXPRESSION
    "YES.*YES.*YES.*YES.*YES.*NO.*NO.*NO.*NO.*NO"
)