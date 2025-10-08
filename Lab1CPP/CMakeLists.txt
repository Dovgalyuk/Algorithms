add_executable(Lab1CPP main.cpp)

target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1CPP
         COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab1CPP PROPERTIES
    PASS_REGULAR_EXPRESSION "osadki = 100")

add_test(NAME TestLab1CPP_Input2
         COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab1CPP_Input2 PROPERTIES
    PASS_REGULAR_EXPRESSION "unic number: 0 1 2 3 4 5 6 7 8 9")