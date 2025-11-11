add_executable(Lab3CPP lab3.cpp)
target_link_libraries(Lab3CPP LibraryCPP)

target_include_directories(Lab3CPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../LibraryCPP)

add_test(NAME TestLab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test_input.txt)
set_tests_properties(TestLab3CPP PROPERTIES PASS_REGULAR_EXPRESSION "B[\r\n]*C")