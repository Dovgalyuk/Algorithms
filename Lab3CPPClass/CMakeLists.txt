add_executable(Lab3CPPClass lab3.cpp)
target_include_directories(Lab3CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab3CPPClass LibraryCPPClass)

add_test(NAME TestMaze1
         COMMAND Lab3CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1.txt)
set_tests_properties(TestMaze1 PROPERTIES
    PASS_REGULAR_EXPRESSION "x.*E")

add_test(NAME TestMaze2
         COMMAND Lab3CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2.txt)
set_tests_properties(TestMaze2 PROPERTIES
    PASS_REGULAR_EXPRESSION "x.*E")

add_test(NAME TestMaze3
         COMMAND Lab3CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test3.txt)
set_tests_properties(TestMaze3 PROPERTIES
    PASS_REGULAR_EXPRESSION "x.*E")

add_test(NAME TestMaze4
         COMMAND Lab3CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test4.txt)
set_tests_properties(TestMaze4 PROPERTIES
    PASS_REGULAR_EXPRESSION "Путь не найден")
