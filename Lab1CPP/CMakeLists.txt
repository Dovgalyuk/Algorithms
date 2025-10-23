add_executable(Lab1CPP main.cpp)
target_include_directories (Lab1CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPP LibraryCPPClass)

add_test(NAME Test_1 COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(Test_1 PROPERTIES PASS_REGULAR_EXPRESSION "0 1 2 3 4 5 6 7 8 9.*1 2 3 4")
add_test(NAME Test_2 COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(Test_2 PROPERTIES PASS_REGULAR_EXPRESSION "22 33 44 88.*3 4")