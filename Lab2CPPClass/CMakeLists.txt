add_executable(Lab2CPPClass calculon.cpp)
target_include_directories(Lab2CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPPClass LibraryCPPClass)

add_test(NAME TestCalculonOriginal
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/Tests/original.txt)

set_tests_properties(TestCalculonOriginal PROPERTIES
    PASS_REGULAR_EXPRESSION "72 101 108 111 44 32 119 114 108 100 33 10"
)

add_test(NAME TestCalculonAddCommand
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/Tests/add-command.txt)

set_tests_properties(TestCalculonAddCommand PROPERTIES
    PASS_REGULAR_EXPRESSION "3"
)

add_test(NAME TestCalculonSubCommand
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/Tests/sub-command.txt)

set_tests_properties(TestCalculonSubCommand PROPERTIES
    PASS_REGULAR_EXPRESSION "1"
)

add_test(NAME TestCalculonMulCommand
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/Tests/mul-command.txt)

set_tests_properties(TestCalculonMulCommand PROPERTIES
    PASS_REGULAR_EXPRESSION "2"
)

add_test(NAME TestCalculonDivCommand
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/Tests/div-command.txt)

set_tests_properties(TestCalculonDivCommand PROPERTIES
    PASS_REGULAR_EXPRESSION "9"
)

add_test(NAME TestCalculonSqrtCommand
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/Tests/sqrt-command.txt)

set_tests_properties(TestCalculonSqrtCommand PROPERTIES
    PASS_REGULAR_EXPRESSION "2"
)

add_test(NAME TestCalculonSqCommand
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/Tests/sq-command.txt)

set_tests_properties(TestCalculonSqCommand PROPERTIES
    PASS_REGULAR_EXPRESSION "16"
)

add_test(NAME TestCalculonGetCommand
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/Tests/get-command.txt)

set_tests_properties(TestCalculonGetCommand PROPERTIES
    PASS_REGULAR_EXPRESSION "0"
)

add_test(NAME TestCalculonCondCommand
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/Tests/cond-command.txt)

set_tests_properties(TestCalculonCondCommand PROPERTIES
    PASS_REGULAR_EXPRESSION "200"
)

add_test(NAME TestCalculonRepeatCommand
         COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/Tests/repeat-command.txt)

set_tests_properties(TestCalculonRepeatCommand PROPERTIES
    PASS_REGULAR_EXPRESSION "5 5 5"
)