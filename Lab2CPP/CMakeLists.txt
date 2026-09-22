add_executable(Lab2Task task.cpp)
target_include_directories(Lab2Task PUBLIC ../LibraryCPP)
target_link_libraries(Lab2Task LibraryCPP)

add_test(NAME TestTask_1 COMMAND Lab2Task ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt)
set_property(TEST TestTask_1 PROPERTY PASS_REGULAR_EXPRESSION "8")

add_test(NAME TestTask_2 COMMAND Lab2Task ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt)
set_property(TEST TestTask_2 PROPERTY PASS_REGULAR_EXPRESSION "105")

add_test(NAME TestTask_3 COMMAND Lab2Task ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt)
set_property(TEST TestTask_3 PROPERTY PASS_REGULAR_EXPRESSION "6")

add_test(NAME TestTask_4 COMMAND Lab2Task ${CMAKE_CURRENT_SOURCE_DIR}/test4.txt)
set_property(TEST TestTask_4 PROPERTY PASS_REGULAR_EXPRESSION "13")

add_test(NAME TestTask_5 COMMAND Lab2Task ${CMAKE_CURRENT_SOURCE_DIR}/test5.txt)
set_property(TEST TestTask_5 PROPERTY PASS_REGULAR_EXPRESSION "10\n10\n10")

add_test(NAME TestTask_6 COMMAND Lab2Task ${CMAKE_CURRENT_SOURCE_DIR}/test6.txt)
set_property(TEST TestTask_6 PROPERTY PASS_REGULAR_EXPRESSION "0\n111\n222\n333")