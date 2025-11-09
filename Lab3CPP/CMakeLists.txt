add_executable(Lab3CPP lab3.cpp)
target_link_libraries(Lab3CPP LibraryCPP)


add_test(NAME TestLab3CPP_1 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(TestLab3CPP_1 PROPERTIES PASS_REGULAR_EXPRESSION "Start City1 City2 End")