add_executable(Lab3CPP main.cpp)

target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_test(
    NAME TestLab3CPP
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
)

set_tests_properties(TestLab3CPP PROPERTIES
    PASS_REGULAR_EXPRESSION "2[\r\n ]+1 2 5[\r\n ]+3 4"
)

add_test(
    NAME TestLab3Connected
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt
)
set_tests_properties(TestLab3Connected PROPERTIES
    PASS_REGULAR_EXPRESSION "1[\r\n ]+1 2 3 4"
)

add_test(
    NAME TestLab3Isolated
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt
)
set_tests_properties(TestLab3Isolated PROPERTIES
    PASS_REGULAR_EXPRESSION "4[\r\n ]+1[\r\n ]+2[\r\n ]+3[\r\n ]+4"
)

add_test(
    NAME TestLab3Single
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt
)
set_tests_properties(TestLab3Single PROPERTIES
    PASS_REGULAR_EXPRESSION "1[\r\n ]+1"
)

add_test(
    NAME TestLab3Mixed
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test4.txt
)
set_tests_properties(TestLab3Mixed PROPERTIES
    PASS_REGULAR_EXPRESSION "3[\r\n ]+1 3 5[\r\n ]+2 4[\r\n ]+6"
)