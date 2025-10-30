add_executable(test_task4 test_task4.c)
target_link_libraries(test_task4 LibraryC)
add_test(NAME ArrayTask4Test COMMAND test_task4)

add_executable(test_task5 test_task5.c)
target_link_libraries(test_task5 LibraryC)
add_test(NAME ArrayTask5Test COMMAND test_task5)