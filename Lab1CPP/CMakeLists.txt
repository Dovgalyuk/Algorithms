add_executable(Lab1CPP main.cpp)

target_include_directories(Lab1CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPP LibraryCPPClass)

add_test(NAME TestLab1CPP
         COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set_tests_properties(TestLab1CPP PROPERTIES
    PASS_REGULAR_EXPRESSION "Factorial array: 1 1 2 6 24 120[ \t\r\n]+Most frequent element: 2")
