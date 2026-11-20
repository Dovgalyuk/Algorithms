add_executable(Task task.cpp)
target_include_directories(Task PUBLIC ../LibraryCPP)
target_link_libraries(Task LibraryCPP)

add_test(NAME TestTask_1 COMMAND Task ${CMAKE_CURRENT_SOURCE_DIR}/task_input.txt)
set_property(TEST TestTask_1 PROPERTY PASS_REGULAR_EXPRESSION
             "^9.*######.*#xxxx#.*#x####.*#xxxx#.*######")

add_test(NAME TestTask_2 COMMAND Task ${CMAKE_CURRENT_SOURCE_DIR}/task_input2.txt)
set_property(TEST TestTask_2 PROPERTY PASS_REGULAR_EXPRESSION
             "^9.*#####.*#xxx#.*#xxx#.*#xxx#.*#####")

add_test(NAME TestTask_3 COMMAND Task ${CMAKE_CURRENT_SOURCE_DIR}/task_input3.txt)
set_property(TEST TestTask_3 PROPERTY PASS_REGULAR_EXPRESSION
             "^1.*#####.*#####.*##x##.*#####.*#####")

add_test(NAME TestTask_4 COMMAND Task ${CMAKE_CURRENT_SOURCE_DIR}/task_input4.txt)
set_property(TEST TestTask_4 PROPERTY PASS_REGULAR_EXPRESSION
             "^3.*#####.*#xxx#.*#####")

add_test(NAME TestTask_5 COMMAND Task ${CMAKE_CURRENT_SOURCE_DIR}/task_input5.txt)
set_property(TEST TestTask_5 PROPERTY PASS_REGULAR_EXPRESSION
             "^15.*xxxx#.*x###x.*x#xxx.*x#x##.*xxx#\\.")

add_test(NAME TestTask_6 COMMAND Task ${CMAKE_CURRENT_SOURCE_DIR}/task_input6.txt)
set_property(TEST TestTask_6 PROPERTY PASS_REGULAR_EXPRESSION
             "Error: no start 'X'")
