add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_test(NAME Test1 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2_1.txt)
add_test(NAME Test2 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2_2.txt)

set_tests_properties(Test1 PROPERTIES PASS_REGULAR_EXPRESSION "YES")
set_tests_properties(Test2 PROPERTIES PASS_REGULAR_EXPRESSION "NO")