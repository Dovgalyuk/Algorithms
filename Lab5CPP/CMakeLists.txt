add_executable(Lab5CPP main.cpp)
target_include_directories (Lab5CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab5CPP LibraryCPPClass)

add_test(NAME Test_1 COMMAND Lab5CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1_5.txt)
set_tests_properties(Test_1 PROPERTIES PASS_REGULAR_EXPRESSION "loaded: 10")