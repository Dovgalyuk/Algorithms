add_executable(Task task.cpp)
target_include_directories(Task PUBLIC ../LibraryCPP)
target_link_libraries(Task LibraryCPP)

add_test(NAME TestTask_1 COMMAND Task ${CMAKE_CURRENT_SOURCE_DIR}/task_input.txt)
set_property(TEST TestTask_1 PROPERTY PASS_REGULAR_EXPRESSION "ABC\\*\\+D\\+")

add_test(NAME TestTask_2 COMMAND Task ${CMAKE_CURRENT_SOURCE_DIR}/task_input2.txt)
set_property(TEST TestTask_2 PROPERTY PASS_REGULAR_EXPRESSION "AB\\*C\\+")

add_test(NAME TestTask_3 COMMAND Task ${CMAKE_CURRENT_SOURCE_DIR}/task_input3.txt)
set_property(TEST TestTask_3 PROPERTY PASS_REGULAR_EXPRESSION "ABCD\\+\\*\\+")

add_test(NAME TestTask_4 COMMAND Task ${CMAKE_CURRENT_SOURCE_DIR}/task_input4.txt)
set_property(TEST TestTask_4 PROPERTY PASS_REGULAR_EXPRESSION "AB-CD\\+-")

add_test(NAME TestTask_5 COMMAND Task ${CMAKE_CURRENT_SOURCE_DIR}/task_input5.txt)
set_property(TEST TestTask_5 PROPERTY PASS_REGULAR_EXPRESSION "Error: invalid expression")

add_test(NAME TestTask_6 COMMAND Task ${CMAKE_CURRENT_SOURCE_DIR}/task_input6.txt)
set_property(TEST TestTask_6 PROPERTY PASS_REGULAR_EXPRESSION "Error: invalid expression")
