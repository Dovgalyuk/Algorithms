add_executable(Lab5CPP lab5.cpp )
target_link_libraries(Lab5CPP LibraryCPP)

add_test(NAME TestLab5CPP COMMAND Lab5CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)

set_tests_properties(TestLab5CPP PROPERTIES PASS_REGULAR_EXPRESSION "Data size: 5000
Bloom filter insert time: PASS
Unordered_set insert time: PASS")
