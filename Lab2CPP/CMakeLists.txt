
add_executable(Lab2CPP
    main.cpp
    ../LibraryCPP/list.cpp
    ../LibraryCPP/stack.cpp
)

target_include_directories(Lab2CPP PRIVATE
    ${CMAKE_SOURCE_DIR}/LibraryCPP
)

add_test(
    NAME Lab2CPPTest1
    COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt
)

set_tests_properties(Lab2CPPTest1 PROPERTIES
    PASS_REGULAR_EXPRESSION "^YES"
)

add_test(
    NAME Lab2CPPTest2
    COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt
)

set_tests_properties(Lab2CPPTest2 PROPERTIES
    PASS_REGULAR_EXPRESSION "^NO"
)

add_test(
    NAME Lab2CPPTest3
    COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt
)

set_tests_properties(Lab2CPPTest3 PROPERTIES
    PASS_REGULAR_EXPRESSION "^NO"
)

add_test(
    NAME Lab2CPPTest4
    COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test4.txt
)

set_tests_properties(Lab2CPPTest4 PROPERTIES
    PASS_REGULAR_EXPRESSION "^YES"
)

