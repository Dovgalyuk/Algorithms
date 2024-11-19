add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_test(NAME Test1 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)

set_tests_properties(Test1 PROPERTIES PASS_REGULAR_EXPRESSION "5")