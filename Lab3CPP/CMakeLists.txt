add_executable(Lab3CPP laba3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_test(NAME TestLab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab3CPP PROPERTIES PASS_REGULAR_EXPRESSION "2\n1 2 5\n3 4")