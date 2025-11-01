add_executable(Lab1CPP main.cpp)

target_include_directories(Lab1CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPP LibraryCPPClass)

# Первый тест: input.txt
add_test(NAME TestLab1CPP
         COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab1CPP PROPERTIES
    PASS_REGULAR_EXPRESSION "Factorial array: 1 1 2 6 24 120[ \t\r\n]+Most frequent element: 2")

# Второй тест: input2.txt
add_test(NAME TestLab1CPP_Input2
         COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)

set_tests_properties(TestLab1CPP_Input2 PROPERTIES
    PASS_REGULAR_EXPRESSION "Factorial array: 1 1 2 6 24 120 720[ \t\r\n]+Most frequent element: 9")