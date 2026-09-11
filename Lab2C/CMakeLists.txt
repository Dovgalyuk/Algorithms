add_executable(Lab2C lab2.c)
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