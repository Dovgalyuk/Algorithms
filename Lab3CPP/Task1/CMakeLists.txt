add_executable(Lab3Task1 main.cpp)

target_include_directories(Lab3Task1 PUBLIC ../../LibraryCPPTemplate)

add_test(NAME Lab3Test1Task1 COMMAND Lab3Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/example.in)
set_property(TEST Lab3Test1Task1 PROPERTY PASS_REGULAR_EXPRESSION "^B\nC\n$")

add_test(NAME Lab3Test2Task1 COMMAND Lab3Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/branches_cycle.in)
set_property(TEST Lab3Test2Task1 PROPERTY PASS_REGULAR_EXPRESSION "^B\nC\nD\nE\n$")

add_test(NAME Lab3Test3Task1 COMMAND Lab3Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/no_reactions.in)
set_property(TEST Lab3Test3Task1 PROPERTY PASS_REGULAR_EXPRESSION "^$")

add_test(NAME Lab3Test4Task1 COMMAND Lab3Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/crlf_spaces.in)
set_property(TEST Lab3Test4Task1 PROPERTY PASS_REGULAR_EXPRESSION "^Hydrogen\nOxygen\n$")

add_test(NAME Lab3Test5Task1 COMMAND Lab3Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/error_format.in)
set_property(TEST Lab3Test5Task1 PROPERTY PASS_REGULAR_EXPRESSION "Invalid reaction at line 3")

add_test(NAME Lab3Test6Task1 COMMAND Lab3Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/no_such_file.in)
set_property(TEST Lab3Test6Task1 PROPERTY PASS_REGULAR_EXPRESSION "cannot open file")
