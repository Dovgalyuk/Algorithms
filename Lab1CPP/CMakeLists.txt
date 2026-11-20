add_executable(Task1 laba1_task1.cpp)
target_link_libraries(Task1 PRIVATE LibraryCPP)

add_executable(Task2 laba1_task2.cpp)
target_link_libraries(Task2 PRIVATE LibraryCPP)

enable_testing()

add_test(NAME test1_task4 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1_1.txt)
set_property(TEST test1_task4 PROPERTY PASS_REGULAR_EXPRESSION "18")

add_test(NAME test2_task4 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1_2.txt)
set_property(TEST test2_task4 PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME test3_task4 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1_3.txt)
set_property(TEST test3_task4 PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME test4_task4 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1_4.txt)
set_property(TEST test4_task4 PROPERTY PASS_REGULAR_EXPRESSION "-3")

add_test(NAME test5_task4 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1_5.txt)
set_property(TEST test5_task4 PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME test1_task5 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2_1.txt)
set_property(TEST test1_task5 PROPERTY PASS_REGULAR_EXPRESSION "5")

add_test(NAME test2_task5 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2_2.txt)
set_property(TEST test2_task5 PROPERTY PASS_REGULAR_EXPRESSION "100")

add_test(NAME test3_task5 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2_3.txt)
set_property(TEST test3_task5 PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME test4_task5 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2_4.txt)
set_property(TEST test4_task5 PROPERTY PASS_REGULAR_EXPRESSION "7")

add_test(NAME test5_task5 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2_5.txt)
set_property(TEST test5_task5 PROPERTY PASS_REGULAR_EXPRESSION "0")

add_custom_target(test_all
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --output-on-failure
    DEPENDS Task1 Task2
)