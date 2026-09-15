add_executable(Lab2C lab2.c maze.c)
target_include_directories(Lab2C PUBLIC ../LibraryC)
target_link_libraries(Lab2C LibraryC)

add_executable(list_tests list_test.c)
target_include_directories(list_tests PUBLIC ../LibraryC)
target_link_libraries(list_tests LibraryC)
add_test(NAME MyListTests COMMAND list_tests)
set_tests_properties(MyListTests PROPERTIES
    PASS_REGULAR_EXPRESSION "0 failed")

add_executable(stack_tests stack_test.c)
target_include_directories(stack_tests PUBLIC ../LibraryC)
target_link_libraries(stack_tests LibraryC)
add_test(NAME MyStackTests COMMAND stack_tests)
set_tests_properties(MyStackTests PROPERTIES
    PASS_REGULAR_EXPRESSION "0 failed")

add_test(NAME HelloWorld COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/maze_hello.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/empty.txt)
set_tests_properties(HelloWorld PROPERTIES
    PASS_REGULAR_EXPRESSION "Hello, world!")

add_test(NAME CatTest COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/maze_cat.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/hello.txt)
set_tests_properties(CatTest PROPERTIES
    PASS_REGULAR_EXPRESSION "Hi")

add_test(NAME TruthMachineTrue COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/truth_machine.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/1.txt)
set_tests_properties(TruthMachineTrue PROPERTIES
    PASS_REGULAR_EXPRESSION "1")

#add_test(NAME TruthMachineFalse COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/truth_machine.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/0.txt)
#set_tests_properties(TruthMachineFalse PROPERTIES  TIMEOUT 3
#    PASS_REGULAR_EXPRESSION "0") # этот тест имеет бесконечный цикл вывода 0, потому я не знаю как это затестить

add_test(NAME DecimalInput COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/decimal_input.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/123.txt)
set_tests_properties(DecimalInput PROPERTIES
    PASS_REGULAR_EXPRESSION "123")

add_test(NAME DisanCount COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/disan_count.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/12.txt)
set_tests_properties(DisanCount PROPERTIES
    PASS_REGULAR_EXPRESSION "0\n2\n4\n6\n8\n10\n12")

add_test(NAME AccumGoesBelowZero COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/my_test.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/empty.txt)
set_tests_properties(AccumGoesBelowZero PROPERTIES
    PASS_REGULAR_EXPRESSION "255")

add_test(NAME StarvedDeath COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/starved_death.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/empty.txt)
set_tests_properties(StarvedDeath PROPERTIES
    PASS_REGULAR_EXPRESSION "hunger")

add_test(NAME OverfeedDeath COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/tests/overfeed.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/empty.txt)
set_tests_properties(OverfeedDeath PROPERTIES
    PASS_REGULAR_EXPRESSION "overfed")
