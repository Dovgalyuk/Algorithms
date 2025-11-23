add_executable(Lab5CPP 
    ${CMAKE_CURRENT_SOURCE_DIR}/lab5.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rbtree.cpp
)

add_test(NAME TestLab5CPP COMMAND Lab5CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab5CPP PROPERTIES PASS_REGULAR_EXPRESSION "loaded: 10")

